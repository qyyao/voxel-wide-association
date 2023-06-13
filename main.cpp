#include "read_nifti.hpp"
#include <array>

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            throw std::runtime_error("Usage: <nifti_file>");
        }

        //get filename from command-line input
        std::string nii_filename = argv[1];

        print_num_subjects(nii_filename);
        print_subject_dimensions(nii_filename, 0);

        int subject_idx = 0;  /* subject index */

        std::array<int, 3> voxel_idx = {64, 64, 28};
        print_voxel_ij(nii_filename, voxel_idx, 0);  

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
