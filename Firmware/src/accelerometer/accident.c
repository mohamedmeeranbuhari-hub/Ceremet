#include <stdbool.h>
#include <stdio.h>

typedef struct {
  float x;
  float y;
  float z;
} AccelData_T;

const float ThresholdAccleration = 2.0f;

static AccelData_T previous_data = {0.0f, 0.0f, 0.0f};

static inline float float_absolute_value(float var) {
  return (var < 0.0f) ? -var : var;
}

bool is_accident_detedted(const AccelData_T *accceration_valueP) {
  // logic
  bool detection = false;

  float delta_x = float_absolute_value(accceration_valueP->x - previous_data.x);
  float delta_y = float_absolute_value(accceration_valueP->y - previous_data.y);

  if (delta_x >= ThresholdAccleration &&
      delta_y >= ThresholdAccleration) { // condition for not break//

    float absolute_value = (accceration_valueP->x * accceration_valueP->x) +
                           (accceration_valueP->y * accceration_valueP->y) +
                           (accceration_valueP->z * accceration_valueP->z);
    if (absolute_value >= (ThresholdAccleration * ThresholdAccleration)) {
      detection = true;
    }
  }

  previous_data = *accceration_valueP;
  return detection;
}

int main(void) {
  AccelData_T sample1 = {0.1f, 10.0f, 1.0f};

  // Call the function!
  if (is_accident_detedted(&sample1)) {
    printf("Accident detected!\n");
  } else {
    printf("Normal ride.\n");
  }
  return 0;
}