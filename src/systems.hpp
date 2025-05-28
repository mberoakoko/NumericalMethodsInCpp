//
// Created by mbero on 21/05/2025.
//
#include <eigen3/Eigen/Core>
#include <functional>
#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP
namespace Systems {
    class ISystem {
    public:
        virtual ~ISystem() = default;
        virtual auto update(float t, Eigen::VectorXd &x, const std::optional<Eigen::VectorXd> &u) -> Eigen::VectorXd = 0; // Pure Virtual
        auto update(const float t, Eigen::VectorXd &x, std::function<std::optional<Eigen::VectorXd>(Eigen::VectorXd)>u) -> Eigen::VectorXd {
            return  update(t, x, u(x));
        }
        auto update(const float t, Eigen::VectorXd& x, std::function<std::optional<Eigen::VectorXd>(float,Eigen::VectorXd)> u) -> Eigen::VectorXd {
            return update(t, x, u(t, x));
        }
        virtual auto output(float t, Eigen::VectorXd &x, const std::optional<Eigen::VectorXd> &u) -> Eigen::MatrixXd = 0; // Pure Virtual

    };
}
#endif //SYSTEMS_HPP
