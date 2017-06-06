#ifndef STANDARDVARS_H
#define STANDARDVARS_H

#include <geometry_msgs/Pose2D.h>

//this file contains variable declarations that are used throught multiple classes such as the Results struct.
using namespace std;

enum PIDType {
    FAST_PID, //quickest turn reasponse time
    SLOW_PID, //slower turn reasponse time
    CONST_PID //constant angular turn rate
};

enum ResultType {
    behavior,
    waypoint,
    precisionDriving
};

enum BehaviorTrigger {
    init,
    targetDropped,
    targetReturned,
    targetLost,
    targetPickedUp
};

struct PrecisionDriving {
    float cmdVel;
    float cmdError;
    float cmdAngular;
};

struct Waypoints {
    int waypointCount;
    geometry_msgs::Pose2D waypoint[50];
};


struct Result {
    
public:
    inline Result() : Result(precisionDriving, -1.0f, -1.0f, FAST_PID) {}
    
    inline Result(ResultType t, float fingerAng, float wristAng, PIDType PID) : type(t), 
                                                                     fingerAngle(fingerAng), 
                                                                     wristAngle(wristAng), 
                                                                     PIDMode(PID) {
        if(this->type == behavior) {
            this->b = init;
        } else if(this->type == waypoint) {
            this->wpts.waypointCount = 0;
        } else if(this->type == precisionDriving) {
            this->pd.cmdVel = 0.0f;
            this->pd.cmdError = 0.0f;
            this->pd.cmdAngular = 0.0f;
        }
    }

    ResultType type;
    union {
        BehaviorTrigger b;
        Waypoints wpts;
        PrecisionDriving pd;
    };
    
    float fingerAngle;
    float wristAngle;
    PIDType PIDMode;
};


/* EXAMPLE:
 * 
 * struct Result res;
 * res.type = ...;
 * res.b = ...;
 * ...
 * 
 * if(res.type == behavior) {
 *      if(res.b == targetDropped) {
 *          ...
 *      } else if(res.b == ...) {
 *          ...
 *      } ...
 * } else if(res.type == waypoint) {
 *      Pose2D next = res.wpts.waypoint[0];
 *      ...
 * } else if(res.type == precisionDriving) {
 *      ...
 * }
 * 
 * 
 * 
 */


#endif // STANDARDVARS_H