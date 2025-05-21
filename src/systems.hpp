//
// Created by mbero on 21/05/2025.
//
#include <eigen3/Eigen/Core>
#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP
namespace Systems {
    class ISystem {
    public:
        virtual ~ISystem() {}
        virtual auto update(float t, const Eigen::VectorXd x, const Eigen::VectorXd& u) -> Eigen::VectorXd = 0;
        virtual auto output(float t, const Eigen::VectorXd x, const Eigen::VectorXd& u) -> Eigen::MatrixXd = 0;
    };
}
#endif //SYSTEMS_HPP
