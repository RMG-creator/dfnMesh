/*! 
 *  @brief     Contains implementation of class DFNFracture
 *  @authors   Pedro Lima
 *  @date      2019
 */

#include "DFNFracture.h"
#include "DFNMesh.h"
#include <math.h>
#include <cstdio>
// #include <unordered_set>
#include <algorithm>
#include "TPZRefPatternDataBase.h"
#include "TPZGeoMeshBuilder.h"
#include "DFNNamespace.h"

#ifdef LOG4CXX
static LoggerPtr logger(Logger::getLogger("dfn.fracture"));
#endif
// const float _2PI = 6.2831853071795865;

// Empty Constructor
DFNFracture::DFNFracture(){
}

// Constructor with corner points, a geomesh and material ID
DFNFracture::DFNFracture(DFNPolygon &Polygon, DFNMesh *dfnMesh)
    :fPolygon(Polygon)
{
    fdfnMesh = dfnMesh;
    // // Set corner nodes of fracture into mesh
    // // @todo I'll remove this after surface meshing is updated to use the SubPolygons
    // if(fdfnMesh->Dimension() == 3){
    //     TPZManVector<int64_t,4> nodeindices = fPolygon.SetPointsInGeomesh(fdfnMesh->Mesh());
    // }
    // fPolygon.FindNodesAbove(fdfnMesh->Mesh());
}

// Copy constructor
DFNFracture::DFNFracture(const DFNFracture &copy){
    this->operator=(copy);
}

// Assignment operator
DFNFracture &DFNFracture::operator=(const DFNFracture &copy){
    fdfnMesh = copy.fdfnMesh;
    fRibs = copy.fRibs;
	fFaces = copy.fFaces;
    fPolygon = copy.fPolygon;
    fSurface = copy.fSurface;
    return *this;
}

/**
 * @brief Get the fracture plane
 * @return The plane corner coordinates
 */

DFNPolygon &DFNFracture::Polygon() {
    return fPolygon;
}











void DFNFracture::AddFace(DFNFace &face){
    int index= face.Index();
    auto res = fFaces.emplace(index,face);
#ifdef LOG4CXX
    if(logger->isDebugEnabled())
    {
        std::stringstream sout;
        sout << "Adding face\n";
        res.first->second.Print(sout,true);
        LOGPZ_DEBUG(logger,sout.str())
    }
#endif
    if(res.second == false) DebugStop();
}
void DFNFracture::AddRib(DFNRib &rib){
    int index= rib.Index();
    auto res = fRibs.emplace(index,rib);
    // Check if the rib is already included
    if(res.second == false) DebugStop();
    #ifdef LOG4CXX
    if(logger->isDebugEnabled())
    {
        std::stringstream sout;
        sout << "Adding rib\n";
        res.first->second.Print(sout);
        LOGPZ_DEBUG(logger,sout.str())
    }
    #endif
}


DFNRib * DFNFracture::Rib(int64_t index){
    auto candidate = fRibs.find(index);
    if(candidate != fRibs.end()){
        return &candidate->second;
    }
    return nullptr;
}
DFNFace * DFNFracture::Face(int64_t index){
    auto candidate = fFaces.find(index);
    if(candidate != fFaces.end()){
        return &candidate->second;
    }
    return nullptr;
}


void DFNFracture::FindFaces(){
    TPZGeoMesh *gmesh = fdfnMesh->Mesh();
    TPZGeoEl *gel;
 
    // iterate over 2D elements and check their 1D neighbours for intersections
    int64_t nel = gmesh->NElements();
    for(int iel=0; iel<nel; iel++){
        gel = gmesh->Element(iel);
        if(!gel)continue;
        if(gel->Dimension() != 2) continue;
        if(gel->HasSubElement() ) continue;
 
        int nnodes = gel->NCornerNodes();
        int nedges = nnodes;
 
        // gather ribs
        TPZManVector<int64_t,4>  rib_index(nedges,-1);
        TPZManVector<DFNRib*,4> rib_vec(nedges,nullptr);
        bool is_intersected = false;
        for(int iedge = 0; iedge < nedges; iedge++){
            TPZGeoElSide gelside(gel,iedge+nnodes);
            TPZGeoElSide neig = gelside.Neighbour();
            for(/*void*/;neig != gelside; neig = neig.Neighbour()){
                if(neig.Element()->Dimension() != 1) continue;
                // @TODO shouldn't you check on the material id? It has to be a skeleton matid
                rib_index[iedge] = neig.Element()->Index();
            }
            if(rib_index[iedge] == -1) DebugStop();
            rib_vec[iedge] = Rib(rib_index[iedge]);
            if(rib_vec[iedge]) is_intersected = true;
        }
        if(!is_intersected) continue;
        
        // build face
        DFNFace face(gel,this);
        // @TODO why not include the rib_index in the constructor?
        face.SetRibs(rib_vec);
        face.UpdateStatusVec();
        // if(!face.IsIntersected()) continue;
        // @TODO Premature, we will check on boundaries later!!
        // what needs to be done is creating DFNRib objects for faces that have only
        // one rib (this means one of its 1D sides are outside the polygon)
        if(face.IsOnBoundary()){
            face.FindInPlanePoint();
        }
        // gel->SetMaterialId(DFNMaterial::Erefined);
        // this method will divide the corresponding geometric face element
        // @TODO where do we check for small angle intersections?
        face.UpdateRefMesh();
        AddFace(face);
    }
}























void DFNFracture::FindRibs(){
    //search gmesh for intersected ribs
    // @TODO It would be more efficient to classify the geometric nodes as
    // being above and below the polygon. Then deciding which ribs are to be
    // divided would be a boolean operation
    int64_t Nels = fdfnMesh->Mesh()->NElements();
    TPZManVector<int64_t, 2> inode(2,0);
    for (int iel = 0; iel < Nels; iel++){
        TPZGeoEl *gel = fdfnMesh->Mesh()->Element(iel);
        if(!gel) continue;
        //skip all elements that aren't ribs
        if (gel->Dimension() != 1){continue;}
        // skip all elements that have been cut by a previous fracture
        if(gel->HasSubElement()){continue;}

        // Check rib
        TPZManVector<REAL,3> intpoint(3,0);
        bool result = fPolygon.Check_rib(gel, intpoint);

        // Add rib
        if (result == true){
            DFNRib rib(gel, this,2);
            rib.SetIntersectionCoord(intpoint);
            // if this 1D element is not part of a previous fracture, change its material to Erefined
            // @TODO I understand that the material id of the skeleton elements is (-1)
            // hardcoded (?) Therefore the only 1d elements would be the ones with
            // material id (-1)?
            if(gel->MaterialId() != DFNMaterial::Efracture) {gel->SetMaterialId(DFNMaterial::Erefined);}
            AddRib(rib);
        }
    }
}


void DFNFracture::RefineRibs(){
    for(auto itr = fRibs.begin(); itr!=fRibs.end(); itr++){
        DFNRib &rib = itr->second;
        rib.Refine();
    }
}
void DFNFracture::RefineFaces(){
    for(auto itr = fFaces.begin(); itr!=fFaces.end(); itr++){
        DFNFace *face = &itr->second;
#ifdef LOG4CXX
        if(logger->isDebugEnabled())
        {
            std::stringstream sout;
            face->Print(sout,true);
            LOGPZ_DEBUG(logger, sout.str())
        }
#endif
        face->Refine();
    }
    fdfnMesh->CreateSkeletonElements(1);
}





void DFNFracture::SnapIntersections_ribs(REAL tolDist){
    for(auto itr = fRibs.begin(); itr!=fRibs.end(); itr++){
        DFNRib* rib = &itr->second;
        rib->SnapIntersection_try(tolDist);
    }
}
void DFNFracture::SnapIntersections_faces(REAL tolDist, REAL tolAngle){
    tolAngle = std::cos(tolAngle);
    for(auto itr = fFaces.begin(); itr!=fFaces.end(); itr++){
        DFNFace* face = &itr->second;
        face->SnapIntersection_try(tolDist, tolAngle);
    }
}













// void DFNFracture::GetOuterLoop(std::vector<int> &loop){
//     TPZGeoMesh* gmesh = fdfnMesh->Mesh();
//     // Compute fracture edges' lenghts
//     int nedges = fPolygon.GetCornersX().Cols();
//     TPZVec<REAL> edgelength(nedges,0);
//     Matrix fraccorners(3,nedges);
//     fraccorners = fPolygon.GetCornersX();
//     for(int i = 0; i < nedges; i++){
//         edgelength[i] = sqrtl(pow(fraccorners(0,i)-fraccorners(0,(i+1)%nedges),2)
//                               +pow(fraccorners(1,i)-fraccorners(1,(i+1)%nedges),2)
//                               +pow(fraccorners(2,i)-fraccorners(2,(i+1)%nedges),2));
//     }
    
// 	// vector of pointers to maps
//     // @todo refactor this to tpzautopointer<map> to prevent memory leak
// 	// TPZManVector<std::map<REAL, int64_t>* > edgemap(nedges);
// 	TPZManVector<TPZAutoPointer<std::map<REAL, int64_t>> > edgemap(nedges);
//     for(int i = 0; i < nedges; i++){
//         edgemap[i] = new std::map<REAL, int64_t>;
//     }
//     // The set of points that have already been checked
//     std::set<int64_t> checked;

//     // iterate over all endfaces and map it to the fracture-edge that cuts it
//     for (auto it = fFaces.begin(); it != fFaces.end(); it++){
//         // get intersection node index and coordinates
//         DFNFace *iface = &it->second;
//         // @todo iface->IsOnBoundary2
//         TPZManVector<REAL,3> ipointcoord = iface->IntersectionCoord();
//         if(ipointcoord.size()<2) continue;
//         int64_t ipointindex = iface->IntersectionIndex();

//         // check if point was already checked
//         auto aux = checked.insert(ipointindex);
//         bool already_checked = !aux.second;
//         if(already_checked) continue;

//         // @todo if(ipointindex == any of the polygon.CornerIndex) continue;
//         // iterate over edges to check if ipoint belongs to it
//         for(int iedge = 0; iedge < nedges; iedge++){
// 			//vectors from ipoint to iedge's nodes
// 			TPZManVector<REAL, 3> v1(3);
// 				v1[0] = fraccorners(0,iedge) - ipointcoord[0];
// 				v1[1] = fraccorners(1,iedge) - ipointcoord[1];
// 				v1[2] = fraccorners(2,iedge) - ipointcoord[2];
// 			TPZManVector<REAL, 3> v2(3);
// 				v2[0] = fraccorners(0,(iedge+1)%nedges) - ipointcoord[0];
// 				v2[1] = fraccorners(1,(iedge+1)%nedges) - ipointcoord[1];
// 				v2[2] = fraccorners(2,(iedge+1)%nedges) - ipointcoord[2];
// 			// square of cross product
// 			REAL temp = pow(v1[1]*v2[2] - v1[2]*v2[1],2);
// 				temp += pow(v1[2]*v2[0] - v1[0]*v2[2],2);
// 				temp += pow(v1[0]*v2[1] - v1[1]*v2[0],2);
// 				temp = sqrtl(temp);
//             // check if point is in edge by calculating if it's normal distance to the edge is zero
//             REAL dist = temp/edgelength[iedge];
// 			if(dist<DFN::gSmallNumber){
// 				// compute local 1D coordinate (alpha)
// 				REAL norm = sqrtl(v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2]);
// 				REAL alpha = norm/edgelength[iedge];
// 				if(alpha > 1+DFN::gSmallNumber){std::cout<<"\nMisattribution of point to edge\n";DebugStop();}
// 				// map intersection indexes from smallest alpha to biggest
//                 // map <alpha, index>
// 				edgemap[iedge]->insert({alpha, ipointindex});
// 			}
//         }
//     }
//     bool warning_message_Q = true;
//     //Once intersections on fracture-edges have been properly ordered and mapped by edge
// 	//iterate over edges to split them
// 	for (int iedge = 0; iedge < nedges; iedge++)
// 	{
// 		int64_t nels = gmesh->NElements();
// 		TPZManVector<int64_t,2> inodes(2);     //index of nodes to be connected
//         int icorner = iedge; //for readability

// 		// connect first end-face intersection to iedge's first node
//         inodes[0] = fPolygon.CornerIndex(icorner);
// 		auto it = edgemap[iedge]->begin();
//         if(edgemap[iedge]->size() == 0){
//             #ifdef PZDEBUG
//                 if(warning_message_Q){
//                     PZError<<"\n Warning: Is there an edge of a fracture that doesn't cut any element? \n\n";
//                     warning_message_Q = false;
//                 }
//             #endif //PZDEBUG
//             // DebugStop();
//         }
//         // iterate over iedge's map
//         while(it != edgemap[iedge]->end()){
//             inodes[1] = it->second;
//             gmesh->CreateGeoElement(EOned, inodes, DFNMaterial::Efracture, nels);
//             loop.push_back((int) nels);
//             inodes[0] = inodes[1];
//             it++;
//         }

// 		// connect last end-intersection to edge last node
//         inodes[1] = fPolygon.CornerIndex((icorner+1)%nedges);
// 		gmesh->CreateGeoElement(EOned, inodes, DFNMaterial::Efracture, nels);
//         loop.push_back((int) nels);
//     }
	
//     gmesh->BuildConnectivity();
//     // correct duplicates
//     int nlines = loop.size();
//     TPZGeoEl* gel;
//     for(int iline=0; iline<nlines; iline++){
//         int iedge = loop[iline];
//         gel = gmesh->Element(iedge);
//         if(!gel || gel->Dimension() != 1) DebugStop();
//         TPZGeoElSide gelside(gel,2);
//         TPZGeoElSide neig = gelside.Neighbour();
//         bool newedge_Q = true;
//         for(/*void*/; neig!=gelside; neig = neig.Neighbour()){
//             if(neig.Element()->Dimension() != 1) continue;
//             // if duplicate, replace in loop and delete duplicate
//             newedge_Q = false;
//             loop[iline] = neig.Element()->Index(); 
//             gmesh->DeleteElement(gel,iedge);
//         }
//         // if it's new, add it to fOutline
//         if(newedge_Q){fOutline.insert({iedge,gel});}
//     }

//     // fix orientation
//     for(int iline=1; iline<nlines; iline++){
//         int iline_index = loop[iline];
//         gel = gmesh->Element(iline_index);
//         int anterior_index = loop[(iline+nlines-1)%nlines];
//         TPZGeoEl *anterior = gmesh->Element(anterior_index);
//         if(gel->NodeIndex(0) != anterior->NodeIndex(1)){
//             loop[iline] *= -1;
//         }
//     }
// }













/**
 * @brief Get an oriented curve loop in gmsh fashion for a 2D element that has 1D neighbours for all its 1D sides
 * @param shift: inform constant shift if you want to shift element indices (+1 is usually the case for gmsh)
*/
void GetCurveLoop(TPZGeoEl* el, std::vector<int> &loop, const int shift=0){
    if(el->Dimension() != 2) DebugStop();
    int nedges = el->NCornerNodes();
    loop.resize(nedges,-1);
    for(int iside=nedges; iside<2*nedges; iside++){
        TPZGeoElSide gelside(el,iside);
        TPZGeoElSide neig = gelside.Neighbour();
        while(neig.Element()->Dimension() != 1){neig = neig.Neighbour();}
        int orientation = (neig.Element()->NodeIndex(0)==el->NodeIndex(iside-nedges)?1:-1);
        loop[iside-nedges] = orientation*(neig.Element()->Index()+shift);
    }
}







// void DFNFracture::MeshFractureSurface_old(){
//     fdfnMesh->Mesh()->BuildConnectivity();
//     // GMsh does not accept zero index entities
//     const int shift = 1;
//     // First construct the edges of the fracture surface
//     std::vector<int> outerLoop;
//     GetOuterLoop(outerLoop);
//     std::vector<TPZGeoEl*> facesInSurface;
//     GetFacesInSurface(facesInSurface);
    
//     // initialize GMsh
//     // gmsh::initialize();
// 	std::string modelname = "modelsurface";
// 	gmsh::model::add(modelname);
//     gmsh::model::setCurrent(modelname);
//     gmsh::option::setNumber("Mesh.Algorithm", 5); // (1: MeshAdapt, 2: Automatic, 5: Delaunay, 6: Frontal-Delaunay, 7: BAMG, 8: Frontal-Delaunay for Quads, 9: Packing of Parallelograms)
//     // INSERT POINTS
//         // iterate over fOutline and get points
//     std::set<int64_t> pointset;
//     {
//         int64_t index = -1;
//         TPZManVector<REAL,3> projcoord(3,0);
//         TPZManVector<REAL,3> realcoord(3,0);
//         for(auto itr : fOutline){
//             TPZGeoEl* gel = itr.second;
//             for(int inode=0; inode<gel->NCornerNodes(); inode++){
//                 index = gel->NodeIndex(inode);
//                 bool newpoint = pointset.insert(index).second;
//                 if(!newpoint){continue;}
//                 gel->NodePtr(inode)->GetCoordinates(realcoord);
//                 projcoord = fPolygon.GetProjectedX(realcoord);
//                 gmsh::model::geo::addPoint(projcoord[0],projcoord[1],projcoord[2],0.,index+shift);

//             }
//         }
//     }
//     // INSERT LINES
//     std::vector<int> curvesInSurface;
//     {
//         for(auto iter = fOutline.begin(); iter != fOutline.end(); iter++){
//             int64_t iel = iter->first+shift;
//             TPZGeoEl *gel = iter->second;
//             if(gel->Dimension() != 1) continue;
//             int64_t node0 = gel->NodeIndex(0)+shift;
//             int64_t node1 = gel->NodeIndex(1)+shift;

//             gmsh::model::geo::addLine(node0,node1,iel);
//             gmsh::model::geo::mesh::setTransfiniteCurve(iel,2); // to reduce number of nodes created by GMsh
//             bool lineIsInEdge = (std::find(outerLoop.begin(),outerLoop.end(),iel-shift) != outerLoop.end());
//             if(lineIsInEdge == false){
//                 curvesInSurface.push_back(iel);
//             }
//         }
//     }
//     // CURVE LOOPS
//         for(auto itr = outerLoop.begin(); itr != outerLoop.end(); itr++){
//             *itr += shift;
//         }
//         int surfaceIndex = 0 + shift;
//         std::vector<int> wiretags(facesInSurface.size()+1,-1);
//         wiretags[0] = gmsh::model::geo::addCurveLoop(outerLoop,surfaceIndex);
//     // Holes in surface
//         for(int iface=0;iface<facesInSurface.size();iface++){
//             TPZGeoEl* face = facesInSurface[iface];
//             std::vector<int> loop;
//             GetCurveLoop(face,loop,shift);
//             wiretags[iface+1] = gmsh::model::geo::addCurveLoop(loop);
//         }

//     // SURFACE + HOLES
//         gmsh::model::geo::addPlaneSurface(wiretags,surfaceIndex);
    
//     // lines in surface
//         // @comment GMsh requires synchronize before embedding geometric entities
//         gmsh::model::geo::synchronize();
//         gmsh::model::mesh::embed(1,curvesInSurface,2,surfaceIndex);
//     // PHYSICAL GROUPS
//         // physical curve
//         int nlines = curvesInSurface.size() + outerLoop.size();
//         if(curvesInSurface.size() > outerLoop.size()){
//             curvesInSurface.reserve(nlines);
//             curvesInSurface.insert(curvesInSurface.end(), outerLoop.begin(), outerLoop.end() );

//             gmsh::model::addPhysicalGroup(1,curvesInSurface,DFNMaterial::Efracture);
//         }else{
//             outerLoop.reserve(nlines);
//             outerLoop.insert(outerLoop.end(), curvesInSurface.begin(), curvesInSurface.end() );

//             gmsh::model::addPhysicalGroup(1,outerLoop,DFNMaterial::Efracture);
//         }
//         // physical surface
//         gmsh::model::addPhysicalGroup(2,{surfaceIndex},DFNMaterial::Efracture);

//     // synchronize before meshing
//         gmsh::model::geo::synchronize();
//     // mesh
//         gmsh::model::mesh::generate(2);
//         // gmsh::model::mesh::optimize("Netgen");
//     // write (for testing)
//         // gmsh::write("testAPI.msh");
//     // import meshed plane back into PZ geoMesh
//         TPZVec<int64_t> newelements;
//         ImportElementsFromGMSH(fdfnMesh->Mesh(),2,pointset,newelements);
//     // close GMsh
//     gmsh::model::remove();
// 	// gmsh::clear();
//     // gmsh::finalize();
    
//     InsertElementsInSurface(newelements);
//     fdfnMesh->CreateSkeletonElements(1, DFNMaterial::Efracture);
// }

void DFNFracture::SetPolygonIndex(std::pair<int64_t,int> face_orient, int polyg_index,TPZVec<std::array<int, 2>>& Polygon_per_face){
	switch(face_orient.second){
		case  1: Polygon_per_face[face_orient.first][0] = polyg_index; break;
		case -1: Polygon_per_face[face_orient.first][1] = polyg_index; break;
		default: DebugStop();
	}
}
int DFNFracture::GetPolygonIndex(std::pair<int64_t,int> face_orient,const TPZVec<std::array<int, 2>>& Polygon_per_face){
	int polyg_index = -1;
	switch(face_orient.second){
		case  1: polyg_index = Polygon_per_face[face_orient.first][0]; break;
		case -1: polyg_index = Polygon_per_face[face_orient.first][1]; break;
		default: DebugStop();
	}
	return polyg_index;
}
std::pair<int64_t,int> DFNFracture::PolyhNeighbour(std::pair<int64_t,int>& currentface_orient, int current_side, int& neig_side){
    int polyh_index = fdfnMesh->GetPolyhedralIndex(currentface_orient);
    if(polyh_index < 0) DebugStop();
    // Loop through 2D neighbours and find the one that shares the same polyhedron
    TPZGeoEl* gel = fdfnMesh->Mesh()->Element(currentface_orient.first);
    TPZGeoElSide gelside(gel,current_side);
    if(gelside.Dimension() != 1) DebugStop();
    TPZGeoElSide neig = gelside.Neighbour();
    for(/*void*/; neig != gelside; neig = neig.Neighbour()){
        if(neig.Element()->Dimension() != 2) continue;
        int64_t neigindex = neig.Element()->Index();
        if(!Face(neigindex)) continue;
        neig_side = neig.Side();
        // To share the same subpolygon, they have to share the same polyhedron
        if(      polyh_index == fdfnMesh->GetPolyhedralIndex({neigindex,+1})){
            return {neigindex,+1};
        }else if(polyh_index == fdfnMesh->GetPolyhedralIndex({neigindex,-1})){
            return {neigindex,-1};
        }
    }
    DebugStop();
    return {-1,0};
}

void DFNFracture::SetLoopOrientation(TPZStack<int64_t>& edgelist){
    int nedges = edgelist.size();
    if(nedges < 3) DebugStop();

    TPZGeoEl* prev_gel = fdfnMesh->Mesh()->Element(edgelist[0]);
    TPZGeoEl* gel = fdfnMesh->Mesh()->Element(edgelist[1]);

    int initialedge_orientation=0;
    if(prev_gel->NodeIndex(1) == gel->NodeIndex(0) ||
       prev_gel->NodeIndex(1) == gel->NodeIndex(1)){
            initialedge_orientation =  1;
    }else{
            initialedge_orientation = -1;
    }

    edgelist[0] *= initialedge_orientation;
    for(int i=1; i<nedges; i++){
        int prev_orientation = (edgelist[i-1]>0?1:-1);
        prev_gel = fdfnMesh->Mesh()->Element(edgelist[i-1]*prev_orientation);
        gel = fdfnMesh->Mesh()->Element(edgelist[i]);
        int prev_node = prev_orientation > 0;
        int orientation = (prev_gel->NodeIndex(prev_node) == gel->NodeIndex(0)?1:-1);
        edgelist[i] *= orientation;
    }
}

TPZGeoEl* DFNFracture::FindCommonNeighbour(TPZGeoElSide& gelside1, TPZGeoElSide& gelside2, int dim){
    TPZGeoMesh* gmesh = gelside1.Element()->Mesh();
    std::set<int64_t> neighbours1;
    std::set<int64_t> neighbours2;

    TPZGeoElSide neig;
    for(neig = gelside1.Neighbour(); neig != gelside1; neig = neig.Neighbour()){
        TPZGeoEl* neig_el = neig.Element();
        if(dim > -1 && neig_el->Dimension() != dim) continue;
        neighbours1.insert(neig_el->Index());
    }
    if(neighbours1.size() < 1) return nullptr;
    for(neig = gelside2.Neighbour(); neig != gelside2; neig = neig.Neighbour()){
        TPZGeoEl* neig_el = neig.Element();
        if(dim > -1 && neig_el->Dimension() != dim) continue;
        neighbours2.insert(neig_el->Index());
    }
    if(neighbours2.size() < 1) return nullptr;

    std::set<int64_t>& smaller_set =  neighbours1.size() > neighbours2.size() ? neighbours2 : neighbours1;
    std::set<int64_t>& bigger_set = !(neighbours1.size() > neighbours2.size()) ? neighbours2 : neighbours1;

    for(auto& iel : smaller_set){
        auto itr = bigger_set.find(iel);
        if(itr == bigger_set.end()) continue;
        return gmesh->Element(*itr);
    }

    
    return nullptr;
}

TPZGeoEl* DFNFracture::FindPolygon(TPZStack<int64_t>& polygon){
    TPZGeoMesh* gmesh = fdfnMesh->Mesh();

    int i=0;
    while(polygon[i]<0) i++;
    TPZGeoEl* gel1 = gmesh->Element(polygon[i]);
    i++;
    while(polygon[i]<0) i++;
    TPZGeoEl* gel2 = gmesh->Element(polygon[i]);

    if(gel1->Dimension() != 1 || gel2->Dimension() != 1) DebugStop();

    TPZGeoElSide gelside1(gel1,2);
    TPZGeoElSide gelside2(gel2,2);

    TPZGeoEl* common_neig = FindCommonNeighbour(gelside1,gelside2,2);

    if(!common_neig) return nullptr;

    common_neig->SetMaterialId(DFNMaterial::Efracture);
    return common_neig;
}

void DFNFracture::MeshFractureSurface(){
    // SubPolygons are subsets of the fracture surface contained by a polyhedral volume
    // A subpolygon is formed whenever (at least) 2 DFNFaces, are refined and part of the same polyhedron
    std::cout<<"\n\n";
    fdfnMesh->CreateSkeletonElements(1);
    TPZVec<std::array<int, 2>> Polygon_per_face(fdfnMesh->Mesh()->NElements(),{-1,-1});
    TPZStack<int64_t> subpolygon(10,-999999);
    int polygon_counter = 0;
    // Loop over DFNFaces
    for(auto& itr : fFaces){
        DFNFace& initial_face = itr.second;

        for(int i=0; i<2; i++){
            int orientation = 1 - 2*i; // (i==0?1:-1)
            // skip 'boundary polyhedron'
            std::pair<int64_t,int> initialface_orient = {initial_face.Index(),orientation};
            if(fdfnMesh->GetPolyhedralIndex(initialface_orient)==0) continue;
            if(fdfnMesh->GetPolyhedralIndex(initialface_orient)< 0) DebugStop();
            if(GetPolygonIndex(initialface_orient,Polygon_per_face) > -1) continue;
            subpolygon.Fill(-999999);
            subpolygon.clear();
            int inletside = initial_face.FirstRibSide();
            SetPolygonIndex(initialface_orient,polygon_counter,Polygon_per_face);
            BuildSubPolygon(Polygon_per_face,initialface_orient,inletside,subpolygon);
            DFN::BulkSetMaterialId(fdfnMesh->Mesh(),subpolygon,DFNMaterial::Efracture);
            
            if(DFN::IsValidPolygon(subpolygon) == false) continue;
            polygon_counter++;
            // Check if would-be polygon already exists in the mesh
            if(FindPolygon(subpolygon)) continue;
            MeshPolygon(subpolygon);
        }
    }
}

void DFNFracture::BuildSubPolygon(TPZVec<std::array<int, 2>>& Polygon_per_face,
                                    std::pair<int64_t,int> currentface_orient,
                                    int inlet_side,
                                    TPZStack<int64_t>& subpolygon)
{
    int polyg_index = GetPolygonIndex(currentface_orient,Polygon_per_face);
    if(polyg_index < 0) DebugStop();

    DFNFace* current_dfnface = Face(currentface_orient.first);
    if(!current_dfnface) DebugStop();
    // add line in face to polygon
    int64_t nextedge = current_dfnface->LineInFace();
    subpolygon.push_back(nextedge);

    // Get next face
    int outlet_side = current_dfnface->OtherRibSide(inlet_side);
    int nextinlet_side = -1;
    std::pair<int64_t,int> nextface_orient = PolyhNeighbour(currentface_orient, outlet_side, nextinlet_side);

    // Check if its set to polygon
    int nextface_polyg_index = GetPolygonIndex(nextface_orient,Polygon_per_face);
    if(nextface_polyg_index < 0){
        SetPolygonIndex(nextface_orient,polyg_index,Polygon_per_face);
        BuildSubPolygon(Polygon_per_face,nextface_orient,nextinlet_side,subpolygon);
    }
    else if(nextface_polyg_index != polyg_index) DebugStop();
}

// void DFNFracture::GetSubPolygons2(){
//     // SubPolygons are subsets of the fracture surface contained by a polyhedral volume
//     // A subpolygon is formed whenever (at least) 2 DFNFaces, are refined and part of the same polyhedron

//     TPZStack<DFNPolyhedron,20>& polyhedra = fdfnMesh->Polyhedra();
//     if(polyhedra.size() < 2){
//         PZError << "\nUninitialized polyhedra stack in DFNMesh\n";
//         DebugStop();
//     }
//     TPZStack<DFNFace*> dfnfaces(10,nullptr);
//     TPZStack<int64_t> polygon;
//     // @todo: std::vector<int> polygon;
//     for(DFNPolyhedron& polyh : polyhedra){
//         // gather DFNFaces that share the same polyhedron
//         dfnfaces.clear();
//         polyh.ListDFNFaces(this,dfnfaces);

//         if(dfnfaces.size() == 2) continue; // TODO review this condition when we start dealing with fracture boundary

//         int nrefined=0;
//         for(auto face : dfnfaces){
//             nrefined += face->NeedsRefinement();
//         }
//     }
    
// }

/// Removes negative integers from a stack
void DFNFracture::ClearNegativeEntries(TPZStack<int64_t>& subpolygon){
    TPZStack<int64_t> copy(subpolygon);
    subpolygon.Fill(-999999);
    subpolygon.clear();
    for(int64_t& index : copy){
        if(index > -1 ) subpolygon.push_back(index);
    }
}

/** @brief Projects a non-planar polygon onto its best fitting plane and uses Gmsh to mesh it
 * @param polygon an oriented loop of edges that don't necessarily occupy the same plane
*/
void DFNFracture::MeshPolygon(TPZStack<int64_t>& polygon){
    // clear collapsed edges from polygon lineloop
    ClearNegativeEntries(polygon);
    // Get set of nodes
    TPZGeoMesh* gmesh = fdfnMesh->Mesh();
    std::set<int64_t> nodes;
    for(int64_t line : polygon){
		TPZGeoEl *gel = gmesh->Element(line);
		nodes.insert(gel->NodeIndex(0));
		nodes.insert(gel->NodeIndex(1));
	}
    int nnodes = nodes.size();
    int nedges = polygon.size();
    
    // If polygon is planar quadrilateral or triangle, we can skip gmsh
    SetLoopOrientation(polygon);
    // std::cout<<"SubPolygon# "<<polygon_counter<<": "<<polygon<<std::endl;
    switch(nnodes){
        case 3: DFN::MeshSimplePolygon(gmesh,polygon,DFNMaterial::Efracture); return;
        case 4: if(DFN::AreCoPlanar(gmesh,nodes))
                    {DFN::MeshSimplePolygon(gmesh,polygon,DFNMaterial::Efracture); return;}
    }

    // Project nodes onto best fitting plane
    TPZManVector<REAL,3> centroid(3,0.);
    TPZManVector<REAL,3> normal(3,0.);
    TPZFMatrix<REAL> nodecloud(3,nnodes);
    int j=0;
	for(int64_t inode : nodes){
	    TPZManVector<REAL,3> coord(3,0.);
		gmesh->NodeVec()[inode].GetCoordinates(coord);
        for(int i=0; i<3; i++){
            nodecloud(i,j) = coord[i];
        }
        j++;
    }
    DFN::BestFitPlane(nodecloud,centroid,normal);
    
    // gmsh::initialize();
	std::string modelname = "model_polyg";
	gmsh::model::add(modelname);
	gmsh::model::setCurrent(modelname);
	std::string mshfilename = "LOG/gmshAPI_polyg.msh";
    gmsh::option::setNumber("Mesh.Algorithm", 5); // (1: MeshAdapt, 2: Automatic, 5: Delaunay, 6: Frontal-Delaunay, 7: BAMG, 8: Frontal-Delaunay for Quads, 9: Packing of Parallelograms)
	// Insert nodes ____________________________________
	{TPZManVector<REAL,3> coord(3,0.);
	TPZManVector<REAL,3> projcoord(3,0.);
	for(int64_t inode : nodes){
		gmesh->NodeVec()[inode].GetCoordinates(coord);
		REAL meshsize = 0.;
        projcoord = DFN::GetProjectedX(coord,centroid,normal);
		gmsh::model::geo::addPoint(projcoord[0],projcoord[1],projcoord[2],meshsize,inode+gmshshift);
	}}
	// Insert lines ____________________________________
    std::vector<int> lineloop;
    lineloop.resize(nedges);
    std::array<int,10> lineloopdebug;
	for(int i=0; i<nedges; i++){
        int64_t iline = abs(polygon[i]);
		TPZGeoEl *gel = gmesh->Element(iline);
		int64_t node0 = gel->NodeIndex(0)+gmshshift;
		int64_t node1 = gel->NodeIndex(1)+gmshshift;
		gmsh::model::geo::addLine(node0,node1,iline+gmshshift);
		gmsh::model::geo::mesh::setTransfiniteCurve(iline+gmshshift,2);
        int orientation = (polygon[i] > 0 ? 1 : -1);
        lineloop[i] = (iline+gmshshift)*orientation;
        lineloopdebug[i] = lineloop[i];
	}
	// Insert faces ____________________________________
    // wiretag is a dummy vector with the shifted index of the face/curve-loop
    std::vector<int> wiretag(1,-1);
    wiretag[0] = gmsh::model::geo::addCurveLoop(lineloop);
    gmsh::model::geo::addPlaneSurface(wiretag,wiretag[0]);
    gmsh::model::addPhysicalGroup(2,wiretag,DFNMaterial::Efracture);
    // gmsh::model::geo::addSurfaceFilling(wiretag,wiretag[0]);
    // gmsh::model::geo::mesh::setTransfiniteSurface(wiretag[0]);
    // gmsh::model::geo::mesh::setRecombine(2,wiretag[0]);

	
	// synchronize before meshing
	gmsh::model::geo::synchronize();
	// mesh
	gmsh::model::mesh::generate(2);
	#ifdef PZDEBUG
		gmsh::write(mshfilename);
	#endif //PZDEBUG
	// import meshed volume back into PZ geoMesh
	std::set<int64_t>& old_nodes = nodes;
    TPZVec<int64_t> newelements;
	ImportElementsFromGMSH(gmesh,2,old_nodes,newelements);
	gmsh::model::remove();
	gmsh::clear();
	// gmsh::finalize();

}


// void DFNFracture::GetSubPolygons_old(){
//     TPZGeoMesh* gmesh = fdfnMesh->Mesh();
//     std::map<int, TPZAutoPointer<std::vector<int>>> subpolygons_map; // @todo maybe change this to a vector of autopointers...
//     // initialize a data structure to track which subpolygons have included which lines
//     std::map<int64_t, std::pair<int,int>> LineTracker;
//     for(auto iterator=fFaces.begin(); iterator!=fFaces.end(); iterator++){
//         DFNFace* face = &iterator->second;
//         int64_t line = face->LineInFace();
//         if(line == -1) continue;
//         LineTracker[line] = {0,0};
//     }
//     TPZManVector<REAL,3> frac_normal(3,0);
//     fPolygon.GetNormal(frac_normal);
//     for(auto iterator=fFaces.begin(); iterator!=fFaces.end(); iterator++){
//         DFNFace* initial_face = &iterator->second;
//         //Check if face intersection is an actual line or has been coalesced down to a point
//         int64_t firstline = initial_face->LineInFace();
//         int current_line = firstline;
//         if(firstline == -1) continue;
//         //Check if the line in face has already been attributed to all its possible subpolygons
//         std::pair<int,int>* tracker = &LineTracker[firstline];
//         int nloops = int(tracker->first>0) + int(tracker->second>0);
//         if(nloops == 2) continue;
//         int npolyhedra = this->fdfnMesh->FaceTracker[initial_face->Index()];
//         // Decide a direction to follow
//         int direction = (tracker->first>0?0:1);
//         // Track if a direction was tried but failed
//         bool DirectionFailed = false;
//         while(nloops < npolyhedra){
//             // TPZAutoPointer<std::vector<int>> subpolygon = new std::vector<int>;
//             // int debugsize = subpolygons_map.size();
//             // std::printf("#%i ---------\n",debugsize);
//             std::vector<int>* subpolygon = new std::vector<int>;

//             // Find next side based in decided direction
//             int nedges = initial_face->GeoEl()->NCornerNodes();
//             int edge;
//             for(edge = 0; edge<nedges; edge++){
//                 DFNRib* edgerib = initial_face->Rib(edge);
//                 if(!edgerib) continue;
//                 if(edgerib->GeoEl()->NodeIndex(0)==gmesh->Element(firstline)->NodeIndex(direction)) break;
//                 if(edgerib->GeoEl()->NodeIndex(1)==gmesh->Element(firstline)->NodeIndex(direction)) break;
//                 if(edgerib->IntersectionIndex()  ==gmesh->Element(firstline)->NodeIndex(direction)) break;
//             }
//             int nextside = edge + initial_face->GeoEl()->NCornerNodes();

//             // Follow direction by getting the next neighbour with the smallest dihedral angle to close the subpolygon
//             TPZGeoEl* current_face = initial_face->GeoEl();
//             do{ //while(current_face != initial_face->GeoEl());
//                 float angle = DFN::_2PI;
//                 if(current_line != -1){
//                     (*subpolygon).push_back(current_line);
//                     // std::cout<<current_line<<std::endl;
//                     if(current_line > 0)    LineTracker[abs(current_line)].first = 1;
//                     else                    LineTracker[abs(current_line)].second = 1;
//                 }
//                 TPZGeoElSide gelside(current_face,nextside);
//                 TPZGeoElSide neig = gelside.Neighbour();
//                 // Check if gelside's side orientation agree's with fracture normal vector
//                 // @todo there's a better way to do this. One that doesn't depend on the fracture polygon. I've done it in GetPolyhedra, so just adapt it here. The orientation of the in-side is the same of the out-side.
//                 TPZManVector<REAL,3> gelside_vec(3,0);
//                 DFN::GetSideVector(gelside,gelside_vec);
//                 int sideorientation;
//                 if(DFN::DotProduct_f(gelside_vec,frac_normal)>0.){
//                     sideorientation = -1;}
//                 else{
//                     sideorientation = 1;
//                 }
//                 TPZGeoEl* next_face;
//                 int current_side = -1;
//                 for(/*void*/; neig!=gelside; neig = neig.Neighbour()){
//                     if(neig.Element()->Dimension() != 2) continue;
//                     if(!Face(neig.Element()->Index())) continue;
//                     float temp_angle = DFN::DihedralAngle(gelside,neig,sideorientation);
//                     if(temp_angle < angle){
//                         angle = temp_angle;
//                         next_face = neig.Element();
//                         current_side = neig.Side();
//                     }
//                 }
//                 if(angle > M_PI+DFN::gSmallNumber){
//                     if(npolyhedra == 1 && !DirectionFailed) {
//                         // Might be an unluckly bad oriented line in initial_face. So try going the other way before DebugStop.
//                         DirectionFailed = true;
//                         direction = (direction+1)%2;
//                         current_line = -firstline;
//                         delete &*subpolygon;
//                         break;
//                     }
//                     PZError << "\nNon-convex regions shouldn't exist at this point\n" << __PRETTY_FUNCTION__ << std::endl;
//                     DebugStop();
//                 }
//                 DirectionFailed = false;
//                 // Get line in face, its orientation and next side
//                 DFNFace* next_dfnface = Face(next_face->Index());
//                 current_line = next_dfnface->LineInFace();
//                 int orientation=0;
//                 for(int iedge=0; iedge < next_face->NCornerNodes(); iedge++){
//                     if(iedge + next_face->NCornerNodes() == current_side) continue;
//                     DFNRib* edge_rib = next_dfnface->Rib(iedge);
//                     if(!edge_rib) continue;
//                     nextside = iedge + next_face->NCornerNodes();
//                     if(current_line != -1){
//                         if(edge_rib->GeoEl()->NodeIndex(0)     ==gmesh->Element(current_line)->NodeIndex(1)) orientation = 1;
//                         else if(edge_rib->GeoEl()->NodeIndex(1)==gmesh->Element(current_line)->NodeIndex(1)) orientation = 1;
//                         else if(edge_rib->IntersectionIndex()  ==gmesh->Element(current_line)->NodeIndex(1)) orientation = 1;
//                         else orientation = -1;
//                     }else{orientation=1;}
//                     break;
//                 }
//                 current_line = orientation*current_line;
//                 current_face = next_face;
//             }while(current_face != initial_face->GeoEl());

//             if(!DirectionFailed){
//                 nloops++;
//                 direction = (direction+1)%2;
//                 // subpolygons_map.insert({subpolygons_map.size(),subpolygon});
//                 if(subpolygon->size() >= 3){ // exception for fractures incorporating an edge of a volume
//                     subpolygons_map[subpolygons_map.size()] = subpolygon;
//                 } 
//             }
//         }
//     }
//     int i_polyg = 0;
//     for(auto iterator=subpolygons_map.begin(); iterator!=subpolygons_map.end(); iterator++){
//         std::vector<int> &polygonloop = *iterator->second;
//         // std::cout<<"\n\nSubPolygon #"<<i_polyg<<"\n";
//         int size = polygonloop.size();
//         for(int iline=0; iline<size; iline++){
//             if(polygonloop[iline] > 0){
//                 std::cout<<" ";
//             }
//             // std::cout<<polygonloop[iline]<<"\n";
//         }
//         i_polyg++;
//     }
// }







































void DFNFracture::ImportElementsFromGMSH(TPZGeoMesh * gmesh, int dimension, std::set<int64_t> &oldnodes, TPZVec<int64_t> &newelements){
    // GMsh does not accept zero index entities
    const int shift = 1;

    // First, if GMsh has created new nodes, these should be inserted in PZGeoMesh
    // create a map <node,point>
    std::map<int,int> mapGMshToPZ;

    for(int64_t pznode : oldnodes){
		std::vector<size_t> node_identifiers;
        std::vector<double> coord;
        std::vector<double> parametricCoord;
        gmsh::model::mesh::getNodes(node_identifiers, coord, parametricCoord,0,pznode+shift,true);
        int gmshnode = (int) node_identifiers[0];
		// insert with hint (since oldnodes is an already sorted set, these nodes will all go in the end)
        mapGMshToPZ.insert(mapGMshToPZ.end(),{gmshnode,pznode+shift});
	}

    // add new nodes into PZGeoMesh
    {
        // get all nodes from GMsh
            std::vector<size_t> node_identifiers;
            std::vector<double> coord;
            std::vector<double> parametricCoord;
            gmsh::model::mesh::getNodes(node_identifiers, coord, parametricCoord);
        // iterate over node_identifiers
        int nnodes = node_identifiers.size();
        for(int i = 0; i < nnodes; i++){
            int gmshnode = node_identifiers[i];
            // check if it is contained in the map
            if(mapGMshToPZ.find(gmshnode) == mapGMshToPZ.end()){
                // New node -> add to PZGeoMesh
                int pznode = (int) gmesh->NodeVec().AllocateNewElement();
                TPZManVector<REAL,3> newnodeX(3);
                newnodeX[0] = coord[3*i];
                newnodeX[1] = coord[3*i+1];
                newnodeX[2] = coord[3*i+2];
                gmesh->NodeVec()[pznode].Initialize(newnodeX,*gmesh);
                // int pznode = (int) gmesh->NNodes();
                // gmesh->NodeVec().resize(pznode+1);
                // insert it in map
                mapGMshToPZ.insert({gmshnode,pznode+shift});
            }

        }
    }
    

    
    int64_t nels = gmesh->NElements();
    std::vector<std::pair<int, int> > dim_to_physical_groups;
    gmsh::model::getPhysicalGroups(dim_to_physical_groups,dimension);
   
    /// inserting the elements
    for (auto group: dim_to_physical_groups) {
       
        int dim = group.first;
        // only want elements of a given dimension
        if(dim != dimension) continue;
        int physical_identifier = group.second;
       
        std::vector< int > entities;
        gmsh::model::getEntitiesForPhysicalGroup(dim, physical_identifier, entities);

		for (auto tag: entities) {
		// std::cout<<"______________________test - tag = "<<tag;
           
            std::vector<int> group_element_types;
            std::vector<std::vector<std::size_t> > group_element_identifiers;
            std::vector<std::vector<std::size_t> > group_node_identifiers;
            gmsh::model::mesh::getElements(group_element_types,group_element_identifiers,group_node_identifiers, dim, tag);
            int n_types = group_element_types.size();
            for (int itype = 0; itype < n_types; itype++){
                int el_type = group_element_types[itype];
                int n_nodes = TPZGeoMeshBuilder::GetNumberofNodes(el_type);
                std::vector<int> node_identifiers(n_nodes);
                int n_elements = group_element_identifiers[itype].size();
                for (int iel = 0; iel < n_elements; iel++) {
                    int el_identifier = group_element_identifiers[itype][iel]-1+nels;
					// std::cout<<"\n"<<el_identifier<<"\n";

                    for (int inode = 0; inode < n_nodes; inode++) {
                        // node_identifiers[inode] = group_node_identifiers[itype][iel*n_nodes+inode];
                        // Use mapGMshToPZ to translate from GMsh node index to PZ nodeindex
                        node_identifiers[inode] = mapGMshToPZ[group_node_identifiers[itype][iel*n_nodes+inode]];
                    }
                    TPZGeoMeshBuilder::InsertElement(gmesh, physical_identifier, el_type, el_identifier, node_identifiers);
					int64_t ntest = gmesh->NElements();
					// std::cout<<"nelements = "<<ntest<<"\n";
                }
            }
        }
    }
    gmesh->BuildConnectivity();
}



















void DFNFracture::Print(std::ostream & out) const
{
    fPolygon.Print(out);
	out << "\n\nDFNRibs:__________\n";
    for(auto itr = fRibs.begin(); itr!=fRibs.end(); itr++){
        const DFNRib *rib = &itr->second;
        rib->Print(out);
    }
	out << "\n\nDFNFaces:_________\n";
    for(auto itr = fFaces.begin(); itr!=fFaces.end(); itr++){
        const DFNFace *face = &itr->second;
        face->Print(out);
    }

    // todo
    // Surface elements
    // SubPolygons
}
