//
// Created by ziqwang on 08.12.21.
//

#ifndef MESHVOXEL_MESHVOXELARAP_H
#define MESHVOXEL_MESHVOXELARAP_H

#include "MeshVoxel.h"
#include "Eigen/Sparse"
#include "igl/arap.h"

class MeshVoxelARAP: public MeshVoxel {
public:

    Eigen::SparseMatrix<double> L_;

    double shape_weight_;

    double gap_;

    igl::ARAPData arap_data_;

    Eigen::MatrixXd R_;

    vector<Eigen::Vector3i> core_voxels;

    vector<Eigen::Vector3i> boundary_voxels;

public:

    MeshVoxelARAP(Eigen::Vector3d ori, double width, int size)
    : MeshVoxel(ori, width, size){
        shape_weight_ = 10.0;
    }

public:

    void readMesh(std::string filename);

    void compute_rotation_matrices(const Eigen::MatrixXd &meshV1);

    void compute_rhs_vectors(Eigen::MatrixXd &rhs);

    void compute_shape_enegry(const Eigen::MatrixXd &meshV1,
                              double &E,
                              Eigen::MatrixXd &gradient) const;

    void compute_energy(const Eigen::MatrixXd &meshV1,
                        double &E,
                        Eigen::MatrixXd &gradient) const;

    void compute_energy(const Eigen::MatrixXd &meshV1,
                        const vector<Eigen::Vector3i> &boundary_voxels,
                        const vector<Eigen::Vector3i> &core_voxels,
                        double tolerance,
                        double &E,
                        Eigen::MatrixXd &gradient) const;

    double line_search(const Eigen::MatrixXd &x,
                       const Eigen::MatrixXd &p,
                       const Eigen::MatrixXd &grad,
                       double init_step = 0.01);

    void precompute_arap_data(const Eigen::VectorXi &b);

    Eigen::MatrixXd solve_arap(Eigen::MatrixXd bc, int num_iters = 10);

    double operator()(const Eigen::VectorXd& x, Eigen::VectorXd& grad) const;

};


#endif //MESHVOXEL_MESHVOXELARAP_H
