#ifndef ALIDIELECTRONPID_H
#define ALIDIELECTRONPID_H

/* Copyright(c) 1998-2009, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

//#############################################################
//#                                                           # 
//#         Class AliDielectronPID                     #
//#                                                           #
//#  Authors:                                                 #
//#   Anton     Andronic, GSI / A.Andronic@gsi.de             #
//#   Ionut C.  Arsene,   GSI / I.C.Arsene@gsi.de             #
//#   Julian    Book,     Uni Ffm / Julian.Book@cern.ch       #
//#   Frederick Kramer,   Uni Ffm, / Frederick.Kramer@cern.ch #
//#   Magnus    Mager,    CERN / Magnus.Mager@cern.ch         #
//#   WooJin J. Park,     GSI / W.J.Park@gsi.de               #
//#   Jens      Wiechula, Uni HD / Jens.Wiechula@cern.ch      #
//#                                                           #
//#############################################################

#include <AliPID.h>
#include <AliAnalysisCuts.h>

class TF1;
class TList;
class AliVTrack;
class TGraph;
class AliPIDResponse;
class AliDielectronVarManager;

class AliDielectronPID : public AliAnalysisCuts {
public:
  enum DetType {kITS, kTPC, kTRD, kTRDeleEff, kTOF, kEMCAL};
  enum PIDbitType {kIgnore=0, kRequire, kIfAvailable};
  
  AliDielectronPID();
  AliDielectronPID(const char*name, const char* title);

  virtual ~AliDielectronPID();

  void AddCut(DetType det, AliPID::EParticleType type, Double_t nSigmaLow, Double_t nSigmaUp=-99999.,
              Double_t min=0, Double_t max=0, Bool_t exclude=kFALSE, UInt_t pidBitType=AliDielectronPID::kRequire, 
	      Int_t var=-1);

  void AddCut(DetType det, AliPID::EParticleType type, Double_t nSigmaLow, TF1 * const funUp,
              Double_t min=0, Double_t max=0, Bool_t exclude=kFALSE, UInt_t pidBitType=AliDielectronPID::kRequire, 
	      Int_t var=-1);

  void AddCut(DetType det, AliPID::EParticleType type, TF1 * const funLow, Double_t nSigmaUp,
              Double_t min=0, Double_t max=0, Bool_t exclude=kFALSE, UInt_t pidBitType=AliDielectronPID::kRequire, 
	      Int_t var=-1);

  void AddCut(DetType det, AliPID::EParticleType type, TF1 * const funLow, TF1 * const funUp,
              Double_t min=0, Double_t max=0, Bool_t exclude=kFALSE, UInt_t pidBitType=AliDielectronPID::kRequire, 
	      Int_t var=-1);
  
  void SetDefaults(Int_t def);

  //
  //Analysis cuts interface
  //const
  virtual Bool_t IsSelected(TObject* track);
  virtual Bool_t IsSelected(TList*   /* list */ ) {return kFALSE;}

  static void SetCorrGraph(TGraph * const gr) { fgFitCorr=gr; }
  static TGraph *GetCorrGraph()  { return fgFitCorr; }
  
  static void SetCorrVal(Double_t run);
  static Double_t GetCorrVal()   { return fgCorr; }
  static Double_t GetCorrValdEdx()   { return fgCorrdEdx; }
  
  static void SetCorrGraphdEdx(TGraph * const gr) { fgdEdxRunCorr=gr; }
  static TGraph *GetCorrGraphdEdx()  { return fgdEdxRunCorr; }

  static void SetEtaCorrFunction(TF1 *fun) {fgFunEtaCorr=fun;}
  static TF1* GetEtaCorrFunction() { return fgFunEtaCorr; }

  static Double_t GetEtaCorr(AliVTrack *track);

private:
  enum {kNmaxPID=10};

  DetType  fDetType[kNmaxPID];    //detector type of nsigma cut
  AliPID::EParticleType fPartType[kNmaxPID]; //particle type
  Float_t  fNsigmaLow[kNmaxPID];  //lower nsigma bound
  Float_t  fNsigmaUp[kNmaxPID];   //upper nsigma bound
  Double_t fmin[kNmaxPID];        //lower cut limit
  Double_t fmax[kNmaxPID];        //upper cut limit
  Bool_t   fExclude[kNmaxPID];    //use as exclusion band
  TF1     *fFunUpperCut[kNmaxPID];//use function as upper cut
  TF1     *fFunLowerCut[kNmaxPID];//use function as lower cut
  UChar_t  fNcuts;                //number of cuts
  UChar_t  fRequirePIDbit[kNmaxPID]; //How to make use of the pid bit (see)
  UShort_t fActiveCuts[kNmaxPID]; // list of activated cuts

  AliPIDResponse *fPIDResponse;   //! pid response object
  
  static TGraph *fgFitCorr;       //spline fit object to correct the nsigma deviation in the TPC electron band
  static Double_t fgCorr;         //!correction value for current run. Set if fgFitCorr is set and SetCorrVal(run)
                                  // was called
  static Double_t fgCorrdEdx;     //!dEdx correction value for current run. Set if fgFitCorr is set and SetCorrVal(run)
                                  // was called
  static TF1    *fgFunEtaCorr;    //function for eta correction of electron sigma
  static TGraph *fgdEdxRunCorr;   //run by run correction for dEdx
  
  Bool_t IsSelectedITS(AliVTrack * const part, Int_t icut);
  Bool_t IsSelectedTPC(AliVTrack * const part, Int_t icut);
  Bool_t IsSelectedTRD(AliVTrack * const part, Int_t icut);
  Bool_t IsSelectedTRDeleEff(AliVTrack * const part, Int_t icut);
  Bool_t IsSelectedTOF(AliVTrack * const part, Int_t icut);
  Bool_t IsSelectedEMCAL(AliVTrack * const part, Int_t icut);

  AliDielectronPID(const AliDielectronPID &c);
  AliDielectronPID &operator=(const AliDielectronPID &c);

  ClassDef(AliDielectronPID,3)         // Dielectron PID
};

#endif
