//
// Created by mbero on 21/05/2025.
//

#ifndef SIM_HPP
#define SIM_HPP
#include <bits/stdc++.h>
#include <eigen3/Eigen/Core>
#include "src/systems.hpp"
namespace Simulator {
    struct SimulationParams {
        double dt;
        double t_final;
    };

    inline auto to_sim_time_vector(const double dt, const double t_final) -> Eigen::VectorXd {
        return Eigen::VectorXd::LinSpaced(round(t_final/dt), 0, t_final);
    };

    inline auto to_sim_time_vector(const SimulationParams& sim_params) -> Eigen::VectorXd {
        return to_sim_time_vector(sim_params.dt, sim_params.t_final);
    }


    class ISimulator {
    public:
        using SystemPtr = std::unique_ptr<Systems::ISystem>;
        explicit ISimulator(SystemPtr  &system, const SimulationParams& params):
        params_(params), t_series_(to_sim_time_vector(params)), system_(std::move(system)){
        }
        virtual ~ISimulator() = default;

        /**
         * Abstract method to perform the simulation of the system
         * @param x_o initial value in vector form
         * @param u forcing of the system
         * @return simulation results
         */
        virtual auto simulate(const Eigen::VectorXd& x_o, const std::optional<Eigen::VectorXd> &u) const -> Eigen::MatrixXd = 0;

        auto get_sim_results()  -> Eigen::MatrixXd {
            return sim_results_;
        }

    protected:
        SimulationParams params_;
        Eigen::VectorXd t_series_;
        Eigen::MatrixXd sim_results_ {};
        SystemPtr system_;
    };

    class EulerODESimulator : public ISimulator {
    public:
        explicit EulerODESimulator(SystemPtr &system, const SimulationParams& params): ISimulator(system, params) {};
        ~EulerODESimulator() override = default;
        auto simulate(const Eigen::VectorXd &x_o, const std::optional<Eigen::VectorXd> &u) const -> Eigen::MatrixXd override {
            Eigen::MatrixXd result = Eigen::MatrixXd::Zero(x_o.size(), t_series_.size());
            result.col(0) = x_o;
            auto x_state = x_o;
            for (int index = 0; index < t_series_.rows(); ++index) {
                x_state = x_state + (system_->update(index, x_state, u) * params_.dt);
                Eigen::VectorXd temp = x_state;
                result.col(index) = temp;
            }
            return result;
        };
    };

    class TestSystem final : public Systems::ISystem {
    public:
        auto update(float t, Eigen::VectorXd &x, const std::optional<Eigen::VectorXd> &u) -> Eigen::VectorXd override {
            return Eigen::VectorXd::Ones(4, 1);
        }
        auto output(float t, Eigen::VectorXd &x, const std::optional<Eigen::VectorXd> &u) -> Eigen::MatrixXd override {
            return  x;
        };
    };

    inline auto test_simulation() -> void {
        std::unique_ptr<Systems::ISystem> t_system = std::make_unique<TestSystem>();
        EulerODESimulator ode_solver(t_system, {.dt = 0.01, .t_final = 1.0});
        Eigen::VectorXd x_o = Eigen::VectorXd{{1, 2, 3, 4}};
        std::cout << ode_solver.simulate(x_o, {}) << std::endl;
        // auto sim_results = ode_solver.get_sim_results().get();
    }


}
#endif //SIM_HPP
