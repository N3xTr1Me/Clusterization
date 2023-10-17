#include "./data_structures/point_tests.h"
#include "./data_structures/domain_tests.h"
#include "./data_structures/target_tests.h"


int main() {

    State::call().disable_notification();

    Point_tests::run_tests();
    Domain_tests::run_tests();
    Target_tests::run_test();

    return 0;

}