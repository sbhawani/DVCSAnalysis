#ifndef MATHKINEMATICVARIABLE_H
#define MATHKINEMATICVARIABLE_H

#include <TLorentzVector.h>


double math_Q2(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron);

double math_Nu(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron);

double math_xB(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron, const double target_mass);

double math_W(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron, const double target_mass);

double math_s(const TLorentzVector& p4_beam, const double target_mass);

double math_y(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron, const double target_mass);

double math_t(const TLorentzVector& p4_recoil, const double target_mass);


#endif // MATHKINEMATICVARIABLE_H