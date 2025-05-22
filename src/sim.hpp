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
        return Eigen::VectorXd::LinSpaced(round(dt/t_final), 0, t_final);
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
        virtual auto simulate(const Eigen::VectorXd& x_o, const std::optional<Eigen::VectorXd> &u) const ->  Eigen::VectorXd = 0;

    protected:
        SimulationParams params_;
        Eigen::VectorXd t_series_;
        SystemPtr system_;
    };

    class EulerODESimulator : public ISimulator {
    public:
        explicit EulerODESimulator(SystemPtr &system, const SimulationParams& params): ISimulator(system, params) {};
        ~EulerODESimulator() override = default;
        auto simulate(const Eigen::VectorXd &x_o, const std::optional<Eigen::VectorXd> &u) const -> Eigen::VectorXd override {
            auto n_dims = x_o.rows();
            auto m_slots = t_series_.rows();
            Eigen::VectorXd result = Eigen::VectorXd::Zero(m_slots, n_dims);
            Eigen::VectorXd x_cache = x_o;
            result(0) = x_cache.value();
            for (int index = 1; index < m_slots; ++index) {
                params_.dt * system_->update(t_series_(index), x_cache, u);
            }
            return  result;
        };
    };

    class TestSystem final : public Systems::ISystem {
    public:
        auto update(float t, const Eigen::VectorXd x, const std::optional<Eigen::VectorXd> &u) -> Eigen::VectorXd override {
            return Eigen::VectorXd::Ones(4, 1);
        }
        auto output(float t, Eigen::VectorXd x, const std::optional<Eigen::VectorXd> &u) -> Eigen::MatrixXd override {
            return  x;
        };
    };

    inline auto test_simulation() -> void {
        std::unique_ptr<Systems::ISystem> t_system = std::make_unique<TestSystem>();
        EulerODESimulator ode_solver(t_system, {.dt = 0.01, .t_final = 1.0});
    }


}
#endif //SIM_HPP
