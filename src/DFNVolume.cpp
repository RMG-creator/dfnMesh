/*! 
 *	DFNVolume.cpp
 *  @author     Pedro Lima
 *  @date       2019
 */

#include "DFNVolume.h"

// Empty constructor
DFNVolume::DFNVolume(){
    fVolumeIndex = -1;
    fIsCut = false;
}

//Constructor
DFNVolume::DFNVolume(int64_t index, bool iscut){
    fVolumeIndex = index;
    fIsCut = iscut;
}

/// Copy constructor
DFNVolume::DFNVolume(const DFNVolume &copy){
    this->operator=(copy);
}

/// Assignment operator
DFNVolume &DFNVolume::operator=(const DFNVolume &copy){
    fVolumeIndex = copy.fVolumeIndex;
    fIsCut = copy.fIsCut;
    fSubEls = copy.fSubEls;
    fIntersection = copy.fIntersection;
    return *this;
}

/// Define the element index and whether it cuts the plane
void DFNVolume::SetElementIndex(int64_t elindex, bool iscut){
    fVolumeIndex = elindex;
    fIsCut = iscut;
}

/// Element index
int64_t DFNVolume::ElementIndex() const{
    return fVolumeIndex;
}

/// Intersects the plane or not
bool DFNVolume::IsCut() const{
    return fIsCut;
}

/// Return the subelement indices
TPZVec<int64_t> DFNVolume::SubElements() const{
    return fSubEls;
}

/// Set the subelement indices
void DFNVolume::SetChildren(const TPZVec<int64_t> &subels){
    fSubEls = subels;
}

/// Set a 2D element enclosed by the volume
void DFNVolume::SetFaceInVolume(int64_t Elindex){
    int N = fEnclosedFaces.size();
    fEnclosedFaces.resize(N+1);
    fEnclosedFaces[N] = Elindex;
}