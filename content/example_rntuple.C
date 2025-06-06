#include <ROOT/RNTupleModel.hxx>
#include <ROOT/RNTupleWriter.hxx>
 
#include <TMath.h>
#include <TRandom.h>
#include <TSystem.h>
 
#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>
#include <utility>
 
using RNTupleModel = ROOT::RNTupleModel;
using RNTupleWriter = ROOT::RNTupleWriter;
 
constexpr char const* kNTupleFileName = "example_rntuple.root";
constexpr int kNEvents = 5;
constexpr int lepIds[4] = {11, -11, 13, -13};

struct MET {
   float et;
   float phi;
};
 
void example_rntuple()
{
   auto model = RNTupleModel::Create();
 
   auto fldTrig   = model->MakeField<bool>("trig");
   auto fldMET    = model->MakeField<MET>("met");
   auto fldLepPid = model->MakeField<std::vector<int>>("lep_pid");
 
   auto ntuple = RNTupleWriter::Recreate(std::move(model), "ntpl", kNTupleFileName);
 
   gRandom->SetSeed(42);
   for (int i = 0; i < kNEvents; i++) {
      *fldTrig = gRandom->Rndm() > 0.5;

      fldMET->et   = gRandom->Rndm()*100;
      fldMET->phi  = (2*gRandom->Rndm() - 1)*TMath::Pi();
 
      fldLepPid->clear();
      int nlep = gRandom->Integer(5);
      for (int j = 0; j < nlep; ++j) {
         fldLepPid->emplace_back(lepIds[gRandom->Integer(4)]);

      }
 
      ntuple->Fill();
   }
}
