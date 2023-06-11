#include "read_nifti.hpp"
#include <array>


void print_voxel_ij(const std::string& nii_filename, const std::array<int, 3>& voxel_idx, int subject_idx) {
    // Read the nifti image
    nifti_image* nii_img = nifti_image_read(nii_filename.c_str(), 1);
    if (!nii_img) {
        throw std::runtime_error("ERROR: could not read NIfTI file " + nii_filename);
    }

    // Calculate the total number of voxels and subjects
    int n_voxels = nii_img->nx * nii_img->ny * nii_img->nz;
    int n_subjects = nii_img->dim[4];

    // Check if the subject index is within the range
    if (subject_idx < 0 || subject_idx >= n_subjects) {
        throw std::runtime_error("ERROR: subject index " + std::to_string(subject_idx) + " out of range [0, " + std::to_string(n_subjects) + ")");
    }

    // Convert the 3D voxel index to a linear index
    int voxel_linear_idx = voxel_idx[0] + voxel_idx[1]*nii_img->nx + voxel_idx[2]*nii_img->nx*nii_img->ny;
    if (voxel_linear_idx < 0 || voxel_linear_idx >= n_voxels) {
        throw std::runtime_error("ERROR: voxel index (" + std::to_string(voxel_idx[0]) + ", " + std::to_string(voxel_idx[1]) + ", " + std::to_string(voxel_idx[2]) + ") out of range");
    }

    // Process the voxel values depending on the data type
    if (nii_img->datatype == DT_FLOAT32) {
        // If the data type is float
        float* data = (float*) nii_img->data;
        float y = data[subject_idx * n_voxels + voxel_linear_idx];
        std::cout << "Voxel at (" << voxel_idx[0] << ", " << voxel_idx[1] << ", " << voxel_idx[2] << ") for subject " << subject_idx << ": " << y << '\n';
    } else if (nii_img->datatype == DT_UNSIGNED_CHAR) {
        // If the data type is unsigned char
        unsigned char* data = (unsigned char*) nii_img->data;
        unsigned char y = data[subject_idx * n_voxels + voxel_linear_idx];
        std::cout << "Voxel at (" << voxel_idx[0] << ", " << voxel_idx[1] << ", " << voxel_idx[2] << ") for subject " << subject_idx << ": " << (int)y << '\n';
    } else {
        throw std::runtime_error("ERROR: unexpected data type " + std::to_string(nii_img->datatype));
    }

    // Free the memory
    nifti_image_free(nii_img);
}

void print_num_subjects(const std::string& nii_filename) {
    // Read the nifti image
    nifti_image* nii_img = nifti_image_read(nii_filename.c_str(), 1);
    if (!nii_img) {
        throw std::runtime_error("ERROR: could not read NIfTI file " + nii_filename);
    }

    // Print the number of subjects
    std::cout << "Number of subjects: " << nii_img->dim[4] << '\n';

    // Free the memory
    nifti_image_free(nii_img);
}

void print_subject_dimensions(const std::string& nii_filename, int subject_index) {
    // Read the nifti image
    nifti_image* nii_img = nifti_image_read(nii_filename.c_str(), 1);
    if (!nii_img) {
        throw std::runtime_error("ERROR: could not read NIfTI file " + nii_filename);
    }

    // Check if the subject index is within the range
    if (subject_index < 0 || subject_index >= nii_img->dim[4]) {
        throw std::runtime_error("ERROR: subject index " + std::to_string(subject_index) + " out of range");
    }

    // Print the dimensions for the given subject
    std::cout << "Dimensions for subject " << subject_index << ": (" << nii_img->nx << ", " << nii_img->ny << ", " << nii_img->nz << ")\n";

    // Free the memory
    nifti_image_free(nii_img);
}
