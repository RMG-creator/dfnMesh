verify volume of polyhedra meshed by gmsh and debugStop if not match








# Ongoing

- [ ] HANDLING ELEMENTS WITH BAD ASPECT RATIO
  - [ ] Discard bad elements and project plane mesh to where nodes were snapped
  - [ ] Formalize logic behind bad-elements-handling
  - [x] Check if rib cut happens too close to vertex 
    - [ ] Two ribs leave the same vertex, point element should be the same
          @notes: 1 element can't have 2 fathers... gotta figure out how this will affect the code downstream
    - [ ] Fracture through a vertex isn't perfect yet... the overlapping of (at least 3) edges coming out of the same vertex needs fixing
  - [ ] Check if face intersection happens too close to rib 
  - [ ] Check if face intersection happens too close to vertex 
  - [ ] Use split-case id inside FractureMesh::FindFaces to define if we're currently in a special case and what should be done about it
  - [ ] Search for critical cases 
    - [ ] Fractures that are almost parallel to mesh plane 
    - [ ] Fracture that overlaps mesh plane should not divide anything, but rather incorporate mesh ribs onto its plane to define the fracture outline.
      - [ ] The problem with this, is that fracture surface mesh would be made up of MHM faces. This is a considerably different code than the one we've written so far.
      - [ ] A probable solution for this would be using GMsh to mesh all planes parallel to fracture surface (one at a time) in order to keep the father->children structure.
        - [ ] If so, it might help to define another map for faces that are parallel to fracPolygon.
- [ ] Geometrical center -> Centroid (in documentation)




# ToDo
- [ ] Face splitting 
  - [ ] Quadrilateral splitting 
    - [ ] Case 9 (No ribs 2) https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
    - [ ] Special case
  - [ ] Triangle splitting 
    - [ ] Case 16 (No ribs 2) https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
    - [ ] Special case
- [ ] Tetrahedralization on volumetric mesh (gmesh should do it) 
  - [ ] GMsh suffers to define a 3D mesh in a volume that requires pyramids
- [ ] Id volumes that contain fracture corners 
  - [ ] Check if point is too close to vertex -> rib -> face 


# Done and Documented
- [x] Rib class
- [x] Face class
- [x] Fracture Plane class
  - [x] Check data consistency
  - [x] Compute axis
  - [x] Compute area
- [x] Fracture Mesh class
  - [x] Map of ribs
  - [x] Map of Mid-Faces
  - [x] Map of End-Faces
- [x] Create skeleton mesh
  - [x] Check if element already has skeleton 
- [x] Check if point is above or bellow plane
- [x] Check if rib is cut by infinite plane
- [x] Calculate intersection with inifinite plane
- [x] Check if intersection is within plane boundaries
  - [x] Compute area of triangles from every corner of plane to point
  - [x] Compare area of triangles to area of plane (to a tolerance)
- [x] Find faces that are cut
  - [x] Iterate over faces
  - [x] Iterate over its 1D neighbours through 1D sides
  - [x] Store in mid-faces if has 2 ribs cut
  - [x] Store in end-faces if has 1 rib cut
- [x] Find intersection points in end-faces
  - [x] figure out 'prettiest' conversion from TPZGeoEl to DFNPolygon
  - [x] create EPoint for intersection points 
- [x] Connect intersection points to define fracture surface outline
  - [x] Connect them at the time an intersected face is found and pair of points are created
- [x] Split fracture front (fracture surface edges)
  - [x] iterate over end-faces
  - [x] find which edge cuts them
  - [x] sort them
  - [x] connect points accordingly
- [x] Change comparisons from a == b to $|a-b|<\varepsilon$
- [x] Insert second plane
  - [x] Implement triangle splitting cases
  - [x] Set a second plane in main
  - [x] Call FindRibs and FindFaces
  - [x] Set RefPatterns
    - [x] Refpattern for ribs shouldn't be uniform
  - [x] Use PZ's data structure to specify level of element splitting
- [X] Swap pzgeoel::NNodes() for pzgeoel::NCornerNodes where necessary
- [x] Mesh polygon 
  - [X] ~~*Ear-clipping-like algorithm*~~ [2019-09-30] 
  - [x] Legalize triangles 
  - [x] GMsh is doing it perfectly
- [x] Face splitting 
  - [x] Store status of each rib and node
  - [x] Identify case 
  - [x] Store all intersections for each face 
  - [x] Father elements 
  - [x] Quadrilateral splitting 
    - [x] Case 1
    - [x] Case 2
    - [x] Case 3
    - [x] Case 4
    - [x] Case 5
    - [x] Case 6
    - [x] Case 7
    - [x] Case 8 (No ribs 1) 
  - [x] Triangle splitting 
    - [x] Case 10
    - [x] Case 11
    - [x] Case 12
    - [x] Case 13
    - [x] Case 14
    - [x] Case 15 (No ribs 1) 
- [x] Tetrahedralization on volumetric mesh (gmesh should do it) 
  - [x] Search which volume encloses each face
  - [x] Search through 2nd (& 3rd, 4th...) level neighbours until a child of an MHM element is found
  - [x] One volume at a time (to allow for refinement patterns)
  - [x] Inform to volumes what faces lie inside it 
  - [x] **Write geometry to GMSH** 
    - [x] Write points 
    - [x] Write Lines 
    - [x] Define physical groups of lines 
    - [x] Write faces 
    - [x] Define physical groups of faces 
    - [x] Test rules for proper definition of surface loops 
    - [x] Write surface loops 
    - [x] Write volumes 
    - [x] Define physical groups of volumes 
    - [x] Rewrite using gmsh API
    - [x] Check if child is of lower dimension than father
    - [x] When sending stuff to GMsh, there might not be any intact volume, in which case, they must be ignored.
    - [x] Pass a container to ImportElementsFromGMsh with old nodes
    - [x] set transfinite stuff






# Archived
Phil's suggestions
- [ ] Search for volumes that contain corner nodes
  - [ ] Ribs that have that node, are contained by the same volume
  - [ ] Faces that have that node, are contained by the same volume
- [ ] From the fracture outline, contours may be generated and these have an easily found containing volume. All elements in that contour will inevitably belong to the same volume.
- [ ] If eldest ancestor has father ID of an element of higher dimension than itself, then that father ID belongs to a MHM element and that MHM element is the enclosing volume (or enclosing area).
- [ ] If we use fatherID to define enclosing volume, would we hurt the robustness of PZ's MHM methods?

Fran's suggestions
- [x] Search through 2nd (& 3rd, 4th...) level neighbours until a child of an MHM element is found
- [ ] Maybe 2D elements could carry the index of their enclosing volumes, this could be a useful optimization
    if neighbour has enclosing volume
        test for that enclosing volume
        if not found
            test for all 3D neighbours