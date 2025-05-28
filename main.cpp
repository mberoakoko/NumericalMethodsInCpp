#include <iostream>
#include <eigen3/Eigen/Eigen>

#include <src/sim.hpp>
#include <eigen3/Eigen/Core>
#include <bits/stdc++.h>
#include "src/systems.hpp"
#include "src/dynamics/double_integrator_dynamics.hpp"
#include "src/ui/dashboard_application.hpp"
#include <unistd.h>

struct Something {
    std::string name_;
    explicit Something(std::string name) : name_(name) {
        std::cout << "Constructing "<< name << std::endl;
    }
    ~Something() {
        std::cout << "Destructing "<< name_ << std::endl;
    }

    Something(const Something &other) {
        std::cout << "Copy constructor" << std::endl;
    }

    Something &operator=(const Something &other) {
        std::cout << "Copy assignment operator" << std::endl;
        return *this;
    }
};

auto exploring_eigen_functions() {
    Eigen::VectorXd mu = Eigen::VectorXd::Ones(10);
    Eigen::MatrixXd m = Eigen::MatrixXd::Zero(10,10);
    std::cout << mu << std::endl;
    std::cout << mu.transpose() << std::endl;
    std::cout << m << std::endl;
    std::cout << "Row operations " << std::endl;
    std::cout << m.col(1) << std::endl;
    std::vector<int> col_indices {1, 3, 4};
    std::vector<int> row_indices {1, 3, 4};
    Eigen::MatrixXd section = m(Eigen::all, col_indices);
    std::cout<< "Selected all items using std::vector \n" << section << std::endl;
    m(row_indices, col_indices).setConstant(32);
    std::cout<<"Setting values in sections of a matrix \n" << m << std::endl;
    Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic> mask = (m.array() == 0).matrix();
    std::cout<<"This is how the mask looks like " << std::endl;
    std::cout << mask << std::endl;
    // std::cout << m.binaryExpr(mask, [](int a, bool check) { return check ? 100 : 0 ; }) << std::endl;
}

auto eigen_library_combined_with_ranges_library() {
    std::array<double, 10> cache {};
    std::ranges::fill(cache, 10);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> matrix = Eigen::MatrixXd::Zero(10,10);


}

auto some_important_task(const Something& something) {
    std::cout<<"Within the scope of " << __FUNCTION__ << std::endl;
    Something inner = something;
    return inner;
}

int main() {
    // Simulator::test_simulation();
    // eigen_library_combined_with_ranges_library();
    // std::unique_ptr<Systems::ISystem> double_intergrator = std::make_unique<Dynamics::DoubleIntegrator>();
    // Eigen::VectorXd x_state = Eigen::VectorXd::Ones(2);
    Simulator::test_double_integrator_simulation();
    // Dashboard::Application application{};
    // application.run();
    return 0;
}