//
// Created by ziqwang on 08.12.21.
//

#ifndef MESHVOXEL_MESHVOXELARAP_H
#define MESHVOXEL_MESHVOXELARAP_H

#include "MeshVoxel.h"
#include "Eigen/Sparse"
class MeshVoxelARAP: public MeshVoxel {
public:

    Eigen::SparseMatrix<double, Eigen::RowMajor> L_;

    double shape_weight_;

public:

    MeshVoxelARAP(Eigen::Vector3d ori, double width, int size, double ratio)
    : MeshVoxel(ori, width, size, ratio){
        shape_weight_ = 1.0;
    }

public:

    void compute_cotmatrix();

    void readMesh(std::string filename);

    void compute_rotation_matrix(Eigen::MatrixXd P0, Eigen::MatrixXd P1, Eigen::MatrixXd D, Eigen::MatrixXd &R);

    void compute_rotation_matrices(const Eigen::MatrixXd &meshV1, vector<Eigen::MatrixXd> &Rs);

    void compute_rhs_vectors(const vector<Eigen::MatrixXd> &Rs, Eigen::MatrixXd &rhs);

    Eigen::MatrixXd deform(Eigen::VectorXi b, Eigen::MatrixXd bc, int num_iters = 10);

    void compute_shape_enegry(const Eigen::MatrixXd &meshV1,
                              const vector<Eigen::MatrixXd> &Rs,
                              double &E,
                              Eigen::MatrixXd &gradient);


    void compute_energy(const Eigen::MatrixXd &meshV1,
                        const vector<Eigen::MatrixXd> &Rs,
                        double &E,
                        Eigen::MatrixXd &gradient);
};


#endif //MESHVOXEL_MESHVOXELARAP_H
