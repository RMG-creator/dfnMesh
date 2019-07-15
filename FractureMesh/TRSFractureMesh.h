/*! 
 *  @authors   Jorge Ordoñez
 *  @authors   Pedro Lima
 *  @date      2018-2019
 */

#ifndef TRSFractureMesh_h
#define TRSFractureMesh_h

#include "pzfmatrix.h"
#include "pzvec.h"
#include "pzmanvector.h"
#include "pzstack.h"

#include <stdio.h>
#include <tuple>
#include "pzmatrix.h"
#include "pzcompel.h"
#include "pzgeoelbc.h"
#include "TRSRibs.h"
#include "TRSFace.h"
#include "TRSFracPlane.h"
//#include "tpanic.h"

typedef TPZFMatrix<REAL> Matrix;

/*! 
 *  @brief     Compares a geomesh with fracture plane to find intersections.
 *  @details   Intersection search is performed after creation of skeleton
 * elements with TRSFractureMesh::CreateSkeletonElements. Fracture plane should
 *  be a TRSFracPlane.
 *  @authors   Jorge Ordoñez
 *  @authors   Pedro Lima
 *  @date      2018-2019
 */
class TRSFractureMesh
{
private:
    /// Define a default tolerance
    REAL fTolerance = 1.e-4;
    
    /// Map of intersected ribs
    std::map<int64_t,TRSRibs> fRibs;
    
    /// Map of intersected faces
    std::map<int64_t,TRSFace> fFaces;
    
    /// Map of end-fracture faces
    // std::map<int64_t,TRSFace> fEndFaces;

    /// Pointer for the geometric mesh
    TPZGeoMesh *fGMesh;

    /// Bounded plane from a fracture
    TRSFracPlane fracplane;


public:
    
    /// Empty constructor
    TRSFractureMesh();
    
    /// Define the fracture plane from 3 to 4 points
    /// Points should be coplanar
    /// The matrix should be dimension 3xN, each column defining the coordinates
    /// of a point
    TRSFractureMesh(TRSFracPlane &FracPlane, TPZGeoMesh *gmesh);
    
    /// Copy constructor
    TRSFractureMesh(const TRSFractureMesh &copy);
    
    /// Assignment operator
    TRSFractureMesh &operator=(const TRSFractureMesh &copy);
    
    /// Associate the geometric mesh
    void SetgeoMesh(TPZGeoMesh *gmesh){
        fGMesh=gmesh;
    }
    
    /// Access the geomesh
    TPZGeoMesh* GetgeoMesh(){
        return fGMesh;
    }
    
    /// Return the corner nodes of the fracture
    TRSFracPlane GetPlane() const;
    
    /// Modify the default tolerance
    void SetTolerance(REAL tolerance);
    REAL GetTolerance() const;
    
public:
    
    
    /// Return true if the surface needs to be divided
    bool NeedsSurface_Divide(int64_t suface_index, TPZVec<int64_t> interribs) ;
    
    
private:
    
    /// ----Deprecated for IsPointInPlane()----
    bool RibInPlane(TPZVec<REAL> &point) const;
    
    /// Checks neighbour's dimension and returns true if it is equal
    bool HasEqualDimensionNeighbour(TPZGeoElSide &gelside);
   
public:
    
    /// Insert intersection elements of lower dimension in the geometric mesh.
    void CreateSkeletonElements(int dimension, int matid);
    
    /// Divide the one dimensional element by the intersection with the plane
    TRSRibs DivideRib(int element_index);
    
    /// Access the ribs data structure
    void AddRib(TRSRibs rib);
    
    /// Access faces' data structure
    void AddFace(TRSFace face);
    
    /// Access end-fracture faces' data structure
    void AddEndFace(TRSFace face);

    /// Map of ribs
    std::map<int64_t ,TRSRibs> GetRibs();
    
    /// Create the children surfaces
    void CreateSurfaces(int matID);
    
    /// Pointer to rib of index 'index'
    TRSRibs *Rib(int index);
    
    /// Finds intersection point of fracture boundaries and geometric mesh faces
    TPZVec<REAL> FindEndFracturePoint(TRSFace face);
};

#endif /* TRSFractureMesh_h */