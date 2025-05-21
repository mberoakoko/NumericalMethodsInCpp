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
        explicit ISimulator(const SystemPtr &system, const SimulationParams& params):
        params_(params), t_series_(to_sim_time_vector(params)), system_(system) {
        }
        virtual ~ISimulator() = default;
        virtual auto simulate(float t, const Eigen::VectorXd& x_o) ->  Eigen::VectorXd = 0;

    protected:
        SimulationParams params_;
        Eigen::VectorXd t_series_;
        SystemPtr system_;
    };

    class EulerODESimulator : public ISimulator {
    public:
        explicit EulerODESimulator(const SystemPtr &system, const SimulationParams& params): ISimulator(system, params) {};
        auto simulate(float t, const Eigen::VectorXd &x_o) -> Eigen::VectorXd override {
            auto n_dims = x_o.rows();
            auto m_slots = t_series_.rows();
            Eigen::VectorXd result = Eigen::VectorXd::Zero(m_slots, n_dims);
            Eigen::VectorXd x_cache = x_o;
            std::ranges::transform(t_series_, result.begin(),
            [&](auto t_index) {
                return t_index;
            });
            return  result;
        };
    };


}
#endif //SIM_HPP
