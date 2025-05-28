//
// Created by mbero on 23/05/2025.
//

#ifndef DOUBLE_INTEGRATOR_DYNAMICS_HPP
#define DOUBLE_INTEGRATOR_DYNAMICS_HPP
#include "../systems.hpp"
#include <eigen3/Eigen/Core>
#include <bits/stdc++.h>
namespace Dynamics {
    class DoubleIntegrator: public Systems::ISystem {
    public:
        explicit DoubleIntegrator(): Systems::ISystem() {
            initialize_system();
        }
        auto update(float t, Eigen::VectorXd &x, const std::optional<Eigen::VectorXd> &u) -> Eigen::VectorXd override {
            Eigen::VectorXd result;
            if (u.has_value()) {
                result = a * x + (b * u.value());
            }else {
                result = a * x ;
            }
            return result;
        }

        auto output(float t, Eigen::VectorXd &x, const std::optional<Eigen::VectorXd> &u) -> Eigen::MatrixXd override {
            return x;
        }

    private:
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> a = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>(2, 2) ;
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> b = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>(2, 1);

        auto initialize_system() -> void {
            a(0, 1) = 1;
            b(1, 0) = 1;
        };
    };
}
#endif //DOUBLE_INTEGRATOR_DYNAMICS_HPP
