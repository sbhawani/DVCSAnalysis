#include "MathKinematicVariable.h"

double math_Q2(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron) {
    TLorentzVector diff = p4_beam - p4_electron; 
    return -diff.M2();           
}

double math_Nu(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron) {
    return p4_beam.E() - p4_electron.E(); 
}

double math_xB(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron, const double target_mass) {
    double Q2 = math_Q2(p4_beam, p4_electron);
    double Nu = math_Nu(p4_beam, p4_electron);
    return Q2 / (2 * target_mass * Nu); // Proton mass in GeV
}

double math_W(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron, const double target_mass) {
    TLorentzVector p4_target(0.0, 0.0, 0.0, target_mass); // target at rest
    return sqrt((p4_beam + p4_target - p4_electron).M2()); // invariant mass
}

double math_s(const TLorentzVector& p4_beam, const double target_mass) {
    TLorentzVector p4_target(0.0, 0.0, 0.0, target_mass); // target at rest
    return (p4_beam + p4_target).M2(); // invariant mass
}

double math_y(const TLorentzVector& p4_beam, const TLorentzVector& p4_electron, const double target_mass) {
    double Nu = math_Nu(p4_beam, p4_electron);
    double s = math_s(p4_beam, target_mass);
    return (2*target_mass/(s-target_mass*target_mass)) * Nu;
}

double math_t(const TLorentzVector& p4_recoil, const double target_mass) {
    TLorentzVector p4_target(0.0, 0.0, 0.0, target_mass); // target at rest
    return (p4_recoil-p4_target).M2();
}