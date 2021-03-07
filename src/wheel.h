#pragma once

#include "helpers/vector_2.h"

struct Wheel {
  Vector2 m_prevPos;
  Vector2 m_pos;
  Vector2 m_front;
  Vector2 m_force;

  void CalcLateralForce(double maxSlipAngleRadians,
                        double mass,
                        double coefFriction) {
    Vector2 moveSinceLastUpdate = m_pos - m_prevPos;
    moveSinceLastUpdate.Normalize();

    double slipAngle = moveSinceLastUpdate.AngleBetween(m_front);
    slipAngle = std::min(slipAngle, maxSlipAngleRadians);
    slipAngle = std::max(slipAngle, -maxSlipAngleRadians);

    double fractionOfMaxLateralForce = slipAngle / maxSlipAngleRadians;
    double weightOnWheel = mass * 9.81 / 4.0;
    double forceMagnitude =
        fractionOfMaxLateralForce * weightOnWheel * coefFriction;
    m_force = m_front.GetPerpendicular() * forceMagnitude;
  }

};
