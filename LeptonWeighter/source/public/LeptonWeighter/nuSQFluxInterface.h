#ifndef LW_NUSQFLUXINTERFACE_H_
#define LW_NUSQFLUXINTERFACE_H_

#include <LeptonWeighter/Flux.h>
#include <LeptonWeighter/ParticleType.h>
#include <nuSQuIDS/nuSQuIDS.h>

namespace LW {

///\function
///\brief Converts between nuSQuIDS internal representation to LeptonWeighter Particle type, i.e. PDG
ParticleType Convert_nuSQuIDS_Id_To_PDG_Id(unsigned int flv, unsigned int neutype);

///\function
///\brief Returns nuSQuIDS internal representation from LeptonWeighter Particle type, i.e. PDG
///\detail pair.first is the flavor and pair.second is neutype.
std::pair<unsigned int, unsigned int> Convert_PDG_Id_To_nuSQuIDS_Id(ParticleType pt);

///\class
///\brief nuSQUIDS atmospheric flux class
template<typename BaseType = nusquids::nuSQUIDS, typename = typename std::enable_if<std::is_base_of<nusquids::nuSQUIDS,BaseType>::value>::type >
class nuSQUIDSAtmFlux: public Flux {
    private:
        const double GeV = 1.0e9;
        bool atmospheric_height_randomization = false;
    protected:
        nusquids::nuSQUIDSAtm<BaseType> nsqa;
    public:
        using result_type = double;
        result_type EvaluateFlux(const Event& e) const override {
          auto nusq_id = Convert_PDG_Id_To_nuSQuIDS_Id(e.primary_type);
          return nsqa.EvalFlavor(nusq_id.first,cos(e.zenith),e.energy*GeV,nusq_id.second, atmospheric_height_randomization);
        };
        explicit nuSQUIDSAtmFlux(const std::string & nusquids_data_file_path, bool atmospheric_height_randomization = false): nsqa(nusquids::nuSQUIDSAtm<BaseType>(nusquids_data_file_path)), atmospheric_height_randomization(atmospheric_height_randomization) {};
        explicit nuSQUIDSAtmFlux(nusquids::nuSQUIDSAtm<BaseType>&& nsqa, bool atmospheric_height_randomization = false): nsqa(std::move(nsqa)), atmospheric_height_randomization(atmospheric_height_randomization) {};
};

///\class
///\brief nuSQUIDS flux class
class nuSQUIDSFlux: public Flux {
    private:
        const double GeV = 1.0e9;
    protected:
        nusquids::nuSQUIDS nsq;
    public:
        using result_type = double;
        result_type EvaluateFlux(const Event& e) const override {
          auto nusq_id = Convert_PDG_Id_To_nuSQuIDS_Id(e.primary_type);
          return nsq.EvalFlavor(nusq_id.first,e.energy*GeV,nusq_id.second);
        };
        explicit nuSQUIDSFlux(const std::string & nusquids_data_file_path): nsq(nusquids::nuSQUIDS(nusquids_data_file_path)) {};
        explicit nuSQUIDSFlux(nusquids::nuSQUIDS&& nsq): nsq(std::move(nsq)) {};
};

} // namespace LW
#endif
