#include <iostream>
#include <random>
#include <TLorentzVector.h>
#include "./../DreamAN/MathKinematicVariable.h"

int main() {
    //demo TLorentzVector

    double beam_energy = 6.535; // GeV
    double target_mass = 0.938272; // GeV, proton mass


    std::random_device rd;  // random number generator seed
    std::mt19937 gen(rd()); // random number generator
    std::uniform_real_distribution<> distheta(1.0, 179.0); // generate random angle between 1 and 180 degrees
    std::uniform_real_distribution<> disphi(-180.0, 180.0); // generate random angle between -180 and 180 degrees

    double e_theta = distheta(gen); // random theta angle
    double e_phi = disphi(gen); // random phi angle

    double e_E=(beam_energy*target_mass)/(target_mass+beam_energy*(1-cos(e_theta))); //scattered electron energy
    double e_px=e_E*sin(e_theta)*cos(e_phi); // scattered electron px
    double e_py=e_E*sin(e_theta)*sin(e_phi); // scattered electron py
    double e_pz=e_E*cos(e_theta); // scattered electron pz

    double p_E=beam_energy+target_mass-e_E; // recoil energy
    double p_px=-e_px; // recoil px
    double p_py=-e_py; // recoil py
    double p_pz=beam_energy-e_E*cos(e_theta); // recoil pz

    TLorentzVector p4_beam(0.0,0.0,beam_energy,beam_energy); // px, py, pz, E
    TLorentzVector p4_electron(e_px,e_py,e_pz,e_E); // px, py, pz, E
    TLorentzVector p4_recoil(p_px,p_py,p_pz,p_E); // px, py, pz, E
    
    

    std::cout << "------------------- Elastic scattering kinematics test -------------------" << std::endl;
    std::cout << "#################### intial setup ####################" << std::endl;
    std::cout << "p4_beam: (px = " << p4_beam.Px()<<"\t"
              << ", py = " << p4_beam.Py()<<"\t"
              << ", pz = " << p4_beam.Pz()<<"\t"
              << ", E = " << p4_beam.E() << ")" << std::endl;

    std::cout << "p4_electron: (px = " << p4_electron.Px()<<"\t"
              << ", py = " << p4_electron.Py()<<"\t"
              << ", pz = " << p4_electron.Pz()<<"\t"
              << ", E = " << p4_electron.E() << ")" << std::endl;

    std::cout << "p4_recoil: (px = " << p4_recoil.Px()<<"\t"
              << ", py = " << p4_recoil.Py()<<"\t"
              << ", pz = " << p4_recoil.Pz()<<"\t"
              << ", E = " << p4_recoil.E() << ")" << std::endl;

    std::cout << "target_mass = " << target_mass << std::endl;

    std::cout << "#################### Kinematic Variables Calculation ####################" << std::endl;
    // Q2
    double Q2_result = math_Q2(p4_beam, p4_electron);
    // output
    std::cout << "Q2(p4_beam, p4_electron) = " << Q2_result << std::endl;

    // Nu
    double Nu_result = math_Nu(p4_beam, p4_electron);
    // output
    std::cout << "Nu(p4_beam, p4_electron) = " << Nu_result << std::endl;

    // xB
    double xB_result = math_xB(p4_beam, p4_electron, target_mass);
    // output
    std::cout << "xB(p4_beam, p4_electron, target_mass) = " << xB_result << std::endl;

    // y
    double y_result = math_y(p4_beam, p4_electron, target_mass);
    // output
    std::cout << "y(p4_beam, p4_electron, target_mass) = " << y_result << std::endl;

    // W
    double W_result = math_W(p4_beam, p4_electron, target_mass);
    // output
    std::cout << "W(p4_beam, p4_electron, target_mass) = " << W_result << std::endl;

    // s
    double s_result = math_s(p4_beam, target_mass);
    // output
    std::cout << "s(p4_beam, target_mass) = " << s_result << std::endl;

    // t
    double t_result = math_t(p4_recoil, target_mass);
    // output
    std::cout << "t(p4_recoil, target_mass) = " << t_result << std::endl;


    std::cout << "#################### Calculation Tests ####################" << std::endl;
    std::cout << "------ test 1 ------"<< std::endl;
    std::cout << "(s-target_mass^2)*x*y = " << (s_result - target_mass*target_mass)*xB_result*y_result << std::endl;
    std::cout << "{(s-target_mass^2)*x*y-Q2}/Q2 = " << (s_result - target_mass*target_mass)*xB_result*y_result/Q2_result-1 << std::endl;
    if (abs(((s_result - target_mass*target_mass)*xB_result*y_result-Q2_result)/Q2_result) < 1e-6) {
        std::cout << "Q2 = (s-target_mass*target_mass)*x*y test pass" << std::endl;
    } else {
        std::cout << "Q2 = (s-target_mass*target_mass)*x*y test NOT pass!!!!!!!" << std::endl;
    }

    std::cout << "------ test 2 ------"<< std::endl;
    std::cout << "W-targetmass/targetmass = " << (W_result - target_mass)/target_mass << std::endl;
    if (abs((W_result - target_mass)/target_mass) < 1e-6) {
        std::cout << "W = targetmass test pass" << std::endl;
    } else {
        std::cout << "W = targetmass test NOT pass!!!!!!!" << std::endl;
    }

    std::cout << "------ test 3 ------"<< std::endl;
    std::cout << "(Q2-|t|)/Q2 =" << (Q2_result+t_result)/Q2_result << std::endl;
    if (abs((Q2_result+t_result)/Q2_result) < 1e-6) {
        std::cout << "t = -Q2 test pass" << std::endl;
    } else {
        std::cout << "t = -Q2 test NOT pass!!!!!!!" << std::endl;
    }


    return 0;
}