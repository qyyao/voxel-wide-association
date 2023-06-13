#ifndef READ_NIFTI_HPP
#define READ_NIFTI_HPP

#include <nifti1_io.h>
#include <iostream>
#include <stdexcept>
#include <array>


void print_voxel_ij(const std::string& nii_filename, const std::array<int, 3>& voxel_idx, int subject_idx);
void print_num_subjects(const std::string& nii_filename);
void print_subject_dimensions(const std::string& nii_filename, int subject_index);

#endif 
