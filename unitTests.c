#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "printer.h"
#include "reader.h"
#include "analyzer.h"

struct ring_buffer results_reader;

struct ring_buffer expected_struct;

void test_print_usage(void) {
    struct ring_buffer results_printer;

    results_printer.buffer[0].usage = 1.00;
    results_printer.buffer[1].usage = 15.65;
    results_printer.buffer[2].usage = 2.10;
    results_printer.buffer[3].usage = 98.89;
    results_printer.buffer[4].usage = 56.78;

    printf("Running print_usage unit test...\n");

    freopen("print_usage_test.txt", "w", stdout);

    print_usage(&results_printer);

    fclose(stdout);

    freopen("/dev/tty", "w", stdout);

    FILE* file = fopen("print_usage_test.txt", "r");
    if (file == NULL) {
        perror("Error opening output file");
        return;
    }

    char output[200];
    fgets(output, sizeof(output), file);

    char expected[200];
    char input[] = "Total CPU usage: 1.00% Core[1] usage: 15.65% Core[2] usage: 2.10% Core[3] usage: 98.89% Core[4] usage: 56.78% \n";
    strcpy(expected, input); 

    assert(strcmp(output, expected) == 0);
    
    fclose(file);
}

void test_reader(void)
{
    get_core_num();

/*PREPARE EXPECTECT PREVIOUS STRUCT*/

    expected_struct.buffer[0].stats.name[0] = "cpu"; 
    expected_struct.buffer[0].stats.user = 17371855;
    expected_struct.buffer[0].stats.nice = 13514;
    expected_struct.buffer[0].stats.system = 2281642;
    expected_struct.buffer[0].stats.idle = 99677807;
    expected_struct.buffer[0].stats.iowait = 255119;
    expected_struct.buffer[0].stats.irq = 0;
    expected_struct.buffer[0].stats.softirq = 391546;
    expected_struct.buffer[0].stats.steal = 0;
    expected_struct.buffer[0].stats.guest = 0;
    expected_struct.buffer[0].stats.guest_nice = 0;

    expected_struct.buffer[1].stats.name[0] = "cpu0"; 
    expected_struct.buffer[1].stats.user = 4704123;
    expected_struct.buffer[1].stats.nice = 3594;
    expected_struct.buffer[1].stats.system = 545137;
    expected_struct.buffer[1].stats.idle = 24618783;
    expected_struct.buffer[1].stats.iowait = 61454;
    expected_struct.buffer[1].stats.irq = 0;
    expected_struct.buffer[1].stats.softirq = 103556;
    expected_struct.buffer[1].stats.steal = 0;
    expected_struct.buffer[1].stats.guest = 0;
    expected_struct.buffer[1].stats.guest_nice = 0;

    expected_struct.buffer[2].stats.name[0] = "cpu1"; 
    expected_struct.buffer[2].stats.user = 4659566;
    expected_struct.buffer[2].stats.nice = 2499;
    expected_struct.buffer[2].stats.system = 565927;
    expected_struct.buffer[2].stats.idle = 24163506;
    expected_struct.buffer[2].stats.iowait = 55569;
    expected_struct.buffer[2].stats.irq = 0;
    expected_struct.buffer[2].stats.softirq = 177766;
    expected_struct.buffer[2].stats.steal = 0;
    expected_struct.buffer[2].stats.guest = 0;
    expected_struct.buffer[2].stats.guest_nice = 0;

    expected_struct.buffer[3].stats.name[0] = "cpu2"; 
    expected_struct.buffer[3].stats.user = 4371362;
    expected_struct.buffer[3].stats.nice = 3970;
    expected_struct.buffer[3].stats.system = 565246;
    expected_struct.buffer[3].stats.idle = 25024011;
    expected_struct.buffer[3].stats.iowait = 70362;
    expected_struct.buffer[3].stats.irq = 0;
    expected_struct.buffer[3].stats.softirq = 59809;
    expected_struct.buffer[3].stats.steal = 0;
    expected_struct.buffer[3].stats.guest = 0;
    expected_struct.buffer[3].stats.guest_nice = 0;

    expected_struct.buffer[4].stats.name[0] = "cpu3"; 
    expected_struct.buffer[4].stats.user = 3636803;
    expected_struct.buffer[4].stats.nice = 3450;
    expected_struct.buffer[4].stats.system = 605331;
    expected_struct.buffer[4].stats.idle = 25871506;
    expected_struct.buffer[4].stats.iowait = 67733;
    expected_struct.buffer[4].stats.irq = 0;
    expected_struct.buffer[4].stats.softirq = 50414;
    expected_struct.buffer[4].stats.steal = 0;
    expected_struct.buffer[4].stats.guest = 0;
    expected_struct.buffer[4].stats.guest_nice = 0;

/*PREPARE EXPECTECT CURRENT STRUCT*/

    expected_struct.buffer[0].stats.cur_name[0] = "cpu"; 
    expected_struct.buffer[0].stats.cur_user = 282806;
    expected_struct.buffer[0].stats.cur_nice = 1020;
    expected_struct.buffer[0].stats.cur_system = 42682;
    expected_struct.buffer[0].stats.cur_idle = 1695018;
    expected_struct.buffer[0].stats.cur_iowait = 3420;
    expected_struct.buffer[0].stats.cur_irq = 0;
    expected_struct.buffer[0].stats.cur_softirq = 5604;
    expected_struct.buffer[0].stats.cur_steal = 0;
    expected_struct.buffer[0].stats.cur_guest = 0;
    expected_struct.buffer[0].stats.cur_guest_nice = 0;

    expected_struct.buffer[1].stats.cur_name[0] = "cpu0"; 
    expected_struct.buffer[1].stats.cur_user = 69965;
    expected_struct.buffer[1].stats.cur_nice = 321;
    expected_struct.buffer[1].stats.cur_system = 10353;
    expected_struct.buffer[1].stats.cur_idle = 426393;
    expected_struct.buffer[1].stats.cur_iowait = 1093;
    expected_struct.buffer[1].stats.cur_irq = 0;
    expected_struct.buffer[1].stats.cur_softirq = 1573;
    expected_struct.buffer[1].stats.cur_steal = 0;
    expected_struct.buffer[1].stats.cur_guest = 0;
    expected_struct.buffer[1].stats.cur_guest_nice = 0;

    expected_struct.buffer[2].stats.cur_name[0] = "cpu1"; 
    expected_struct.buffer[2].stats.cur_user = 72021;
    expected_struct.buffer[2].stats.cur_nice = 89;
    expected_struct.buffer[2].stats.cur_system = 10269;
    expected_struct.buffer[2].stats.cur_idle = 418890;
    expected_struct.buffer[2].stats.cur_iowait = 797;
    expected_struct.buffer[2].stats.cur_irq = 0;
    expected_struct.buffer[2].stats.cur_softirq = 2160;
    expected_struct.buffer[2].stats.cur_steal = 0;
    expected_struct.buffer[2].stats.cur_guest = 0;
    expected_struct.buffer[2].stats.cur_guest_nice = 0;

    expected_struct.buffer[3].stats.cur_name[0] = "cpu2"; 
    expected_struct.buffer[3].stats.cur_user = 69373;
    expected_struct.buffer[3].stats.cur_nice = 42;
    expected_struct.buffer[3].stats.cur_system = 11304;
    expected_struct.buffer[3].stats.cur_idle = 426112;
    expected_struct.buffer[3].stats.cur_iowait = 786;
    expected_struct.buffer[3].stats.cur_irq = 0;
    expected_struct.buffer[3].stats.cur_softirq = 852;
    expected_struct.buffer[3].stats.cur_steal = 0;
    expected_struct.buffer[3].stats.cur_guest = 0;
    expected_struct.buffer[3].stats.cur_guest_nice = 0;

    expected_struct.buffer[4].stats.cur_name[0] = "cpu3"; 
    expected_struct.buffer[4].stats.cur_user = 71446;
    expected_struct.buffer[4].stats.cur_nice = 568;
    expected_struct.buffer[4].stats.cur_system = 10755;
    expected_struct.buffer[4].stats.cur_idle = 423621;
    expected_struct.buffer[4].stats.cur_iowait = 742;
    expected_struct.buffer[4].stats.cur_irq = 0;
    expected_struct.buffer[4].stats.cur_softirq = 1019;
    expected_struct.buffer[4].stats.cur_steal = 0;
    expected_struct.buffer[4].stats.cur_guest = 0;
    expected_struct.buffer[4].stats.cur_guest_nice = 0;

    get_proc_stats(&results_reader);


/*TEST PREV STATS*/

    assert(expected_struct.buffer[0].stats.user        == results_reader.buffer[0].stats.user &&
            expected_struct.buffer[0].stats.nice        == results_reader.buffer[0].stats.nice &&
            expected_struct.buffer[0].stats.system      == results_reader.buffer[0].stats.system &&
            expected_struct.buffer[0].stats.idle        == results_reader.buffer[0].stats.idle &&
            expected_struct.buffer[0].stats.iowait      == results_reader.buffer[0].stats.iowait &&
            expected_struct.buffer[0].stats.irq         == results_reader.buffer[0].stats.irq &&
            expected_struct.buffer[0].stats.softirq     == results_reader.buffer[0].stats.softirq &&
            expected_struct.buffer[0].stats.steal       == results_reader.buffer[0].stats.steal &&
            expected_struct.buffer[0].stats.guest       == results_reader.buffer[0].stats.guest && 
            expected_struct.buffer[0].stats.guest_nice  == results_reader.buffer[0].stats.guest_nice);

    assert(expected_struct.buffer[1].stats.user         == results_reader.buffer[1].stats.user &&
            expected_struct.buffer[1].stats.nice        == results_reader.buffer[1].stats.nice &&
            expected_struct.buffer[1].stats.system      == results_reader.buffer[1].stats.system &&
            expected_struct.buffer[1].stats.idle        == results_reader.buffer[1].stats.idle &&
            expected_struct.buffer[1].stats.iowait      == results_reader.buffer[1].stats.iowait &&
            expected_struct.buffer[1].stats.irq         == results_reader.buffer[1].stats.irq &&
            expected_struct.buffer[1].stats.softirq     == results_reader.buffer[1].stats.softirq &&
            expected_struct.buffer[1].stats.steal       == results_reader.buffer[1].stats.steal &&
            expected_struct.buffer[1].stats.guest       == results_reader.buffer[1].stats.guest &&
            expected_struct.buffer[1].stats.guest_nice  == results_reader.buffer[1].stats.guest_nice);

    assert(expected_struct.buffer[2].stats.user         == results_reader.buffer[2].stats.user &&
            expected_struct.buffer[2].stats.nice        == results_reader.buffer[2].stats.nice &&
            expected_struct.buffer[2].stats.system      == results_reader.buffer[2].stats.system &&
            expected_struct.buffer[2].stats.idle        == results_reader.buffer[2].stats.idle &&
            expected_struct.buffer[2].stats.iowait      == results_reader.buffer[2].stats.iowait &&
            expected_struct.buffer[2].stats.irq         == results_reader.buffer[2].stats.irq &&
            expected_struct.buffer[2].stats.softirq     == results_reader.buffer[2].stats.softirq &&
            expected_struct.buffer[2].stats.steal       == results_reader.buffer[2].stats.steal &&
            expected_struct.buffer[2].stats.guest       == results_reader.buffer[2].stats.guest &&
            expected_struct.buffer[2].stats.guest_nice  == results_reader.buffer[2].stats.guest_nice);

    assert(expected_struct.buffer[3].stats.user         == results_reader.buffer[3].stats.user &&
            expected_struct.buffer[3].stats.nice        == results_reader.buffer[3].stats.nice &&
            expected_struct.buffer[3].stats.system      == results_reader.buffer[3].stats.system &&
            expected_struct.buffer[3].stats.idle        == results_reader.buffer[3].stats.idle &&
            expected_struct.buffer[3].stats.iowait      == results_reader.buffer[3].stats.iowait &&
            expected_struct.buffer[3].stats.irq         == results_reader.buffer[3].stats.irq &&
            expected_struct.buffer[3].stats.softirq     == results_reader.buffer[3].stats.softirq &&
            expected_struct.buffer[3].stats.steal       == results_reader.buffer[3].stats.steal &&
            expected_struct.buffer[3].stats.guest       == results_reader.buffer[3].stats.guest &&
            expected_struct.buffer[3].stats.guest_nice  == results_reader.buffer[3].stats.guest_nice);

    assert(expected_struct.buffer[4].stats.user         == results_reader.buffer[4].stats.user &&
            expected_struct.buffer[4].stats.nice        == results_reader.buffer[4].stats.nice &&
            expected_struct.buffer[4].stats.system      == results_reader.buffer[4].stats.system &&
            expected_struct.buffer[4].stats.idle        == results_reader.buffer[4].stats.idle &&
            expected_struct.buffer[4].stats.iowait      == results_reader.buffer[4].stats.iowait &&
            expected_struct.buffer[4].stats.irq         == results_reader.buffer[4].stats.irq &&
            expected_struct.buffer[4].stats.softirq     == results_reader.buffer[4].stats.softirq &&
            expected_struct.buffer[4].stats.steal       == results_reader.buffer[4].stats.steal &&
            expected_struct.buffer[4].stats.guest       == results_reader.buffer[4].stats.guest &&
            expected_struct.buffer[4].stats.guest_nice  == results_reader.buffer[4].stats.guest_nice);

/*TEST CURRENT STATS*/

    assert(expected_struct.buffer[0].stats.cur_user        == results_reader.buffer[0].stats.cur_user &&
            expected_struct.buffer[0].stats.cur_nice        == results_reader.buffer[0].stats.cur_nice &&
            expected_struct.buffer[0].stats.cur_system      == results_reader.buffer[0].stats.cur_system &&
            expected_struct.buffer[0].stats.cur_idle        == results_reader.buffer[0].stats.cur_idle &&
            expected_struct.buffer[0].stats.cur_iowait      == results_reader.buffer[0].stats.cur_iowait &&
            expected_struct.buffer[0].stats.cur_irq         == results_reader.buffer[0].stats.cur_irq &&
            expected_struct.buffer[0].stats.cur_softirq     == results_reader.buffer[0].stats.cur_softirq &&
            expected_struct.buffer[0].stats.cur_steal       == results_reader.buffer[0].stats.cur_steal &&
            expected_struct.buffer[0].stats.cur_guest       == results_reader.buffer[0].stats.cur_guest && 
            expected_struct.buffer[0].stats.cur_guest_nice  == results_reader.buffer[0].stats.cur_guest_nice);

    assert(expected_struct.buffer[1].stats.cur_user         == results_reader.buffer[1].stats.cur_user &&
            expected_struct.buffer[1].stats.cur_nice        == results_reader.buffer[1].stats.cur_nice &&
            expected_struct.buffer[1].stats.cur_system      == results_reader.buffer[1].stats.cur_system &&
            expected_struct.buffer[1].stats.cur_idle        == results_reader.buffer[1].stats.cur_idle &&
            expected_struct.buffer[1].stats.cur_iowait      == results_reader.buffer[1].stats.cur_iowait &&
            expected_struct.buffer[1].stats.cur_irq         == results_reader.buffer[1].stats.cur_irq &&
            expected_struct.buffer[1].stats.cur_softirq     == results_reader.buffer[1].stats.cur_softirq &&
            expected_struct.buffer[1].stats.cur_steal       == results_reader.buffer[1].stats.cur_steal &&
            expected_struct.buffer[1].stats.cur_guest       == results_reader.buffer[1].stats.cur_guest &&
            expected_struct.buffer[1].stats.cur_guest_nice  == results_reader.buffer[1].stats.cur_guest_nice);

    assert(expected_struct.buffer[2].stats.cur_user         == results_reader.buffer[2].stats.cur_user &&
            expected_struct.buffer[2].stats.cur_nice        == results_reader.buffer[2].stats.cur_nice &&
            expected_struct.buffer[2].stats.cur_system      == results_reader.buffer[2].stats.cur_system &&
            expected_struct.buffer[2].stats.cur_idle        == results_reader.buffer[2].stats.cur_idle &&
            expected_struct.buffer[2].stats.cur_iowait      == results_reader.buffer[2].stats.cur_iowait &&
            expected_struct.buffer[2].stats.cur_irq         == results_reader.buffer[2].stats.cur_irq &&
            expected_struct.buffer[2].stats.cur_softirq     == results_reader.buffer[2].stats.cur_softirq &&
            expected_struct.buffer[2].stats.cur_steal       == results_reader.buffer[2].stats.cur_steal &&
            expected_struct.buffer[2].stats.cur_guest       == results_reader.buffer[2].stats.cur_guest &&
            expected_struct.buffer[2].stats.cur_guest_nice  == results_reader.buffer[2].stats.cur_guest_nice);

    assert(expected_struct.buffer[3].stats.cur_user         == results_reader.buffer[3].stats.cur_user &&
            expected_struct.buffer[3].stats.cur_nice        == results_reader.buffer[3].stats.cur_nice &&
            expected_struct.buffer[3].stats.cur_system      == results_reader.buffer[3].stats.cur_system &&
            expected_struct.buffer[3].stats.cur_idle        == results_reader.buffer[3].stats.cur_idle &&
            expected_struct.buffer[3].stats.cur_iowait      == results_reader.buffer[3].stats.cur_iowait &&
            expected_struct.buffer[3].stats.cur_irq         == results_reader.buffer[3].stats.cur_irq &&
            expected_struct.buffer[3].stats.cur_softirq     == results_reader.buffer[3].stats.cur_softirq &&
            expected_struct.buffer[3].stats.cur_steal       == results_reader.buffer[3].stats.cur_steal &&
            expected_struct.buffer[3].stats.cur_guest       == results_reader.buffer[3].stats.cur_guest &&
            expected_struct.buffer[3].stats.cur_guest_nice  == results_reader.buffer[3].stats.cur_guest_nice);

    assert(expected_struct.buffer[4].stats.cur_user         == results_reader.buffer[4].stats.cur_user &&
            expected_struct.buffer[4].stats.cur_nice        == results_reader.buffer[4].stats.cur_nice &&
            expected_struct.buffer[4].stats.cur_system      == results_reader.buffer[4].stats.cur_system &&
            expected_struct.buffer[4].stats.cur_idle        == results_reader.buffer[4].stats.cur_idle &&
            expected_struct.buffer[4].stats.cur_iowait      == results_reader.buffer[4].stats.cur_iowait &&
            expected_struct.buffer[4].stats.cur_irq         == results_reader.buffer[4].stats.cur_irq &&
            expected_struct.buffer[4].stats.cur_softirq     == results_reader.buffer[4].stats.cur_softirq &&
            expected_struct.buffer[4].stats.cur_steal       == results_reader.buffer[4].stats.cur_steal &&
            expected_struct.buffer[4].stats.cur_guest       == results_reader.buffer[4].stats.cur_guest &&
            expected_struct.buffer[4].stats.cur_guest_nice  == results_reader.buffer[4].stats.cur_guest_nice);

}

void test_analyzer(void)
{
    expected_struct.buffer[0].usage = 16.82;
    expected_struct.buffer[1].usage = 17.96;
    expected_struct.buffer[2].usage = 18.37;
    expected_struct.buffer[3].usage = 16.73;
    expected_struct.buffer[4].usage = 14.27;

    calculate_usage(&results_reader);

    assert(expected_struct.buffer[0].usage == results_reader.buffer[0].usage);
    assert(expected_struct.buffer[1].usage == results_reader.buffer[1].usage);
    assert(expected_struct.buffer[2].usage == results_reader.buffer[2].usage);
    assert(expected_struct.buffer[3].usage == results_reader.buffer[3].usage);
    assert(expected_struct.buffer[4].usage == results_reader.buffer[4].usage);
}

int main() {
    test_print_usage();
    printf("print_usage test ");
    printf("\033[1;32m");
    printf("PASSED\n");
    printf("\033[0m");

    test_reader();
    printf("reader test ");
    printf("\033[1;32m");
    printf("PASSED\n");
    printf("\033[0m");

    test_analyzer();
    printf("analyzer test ");
    printf("\033[1;32m");
    printf("PASSED\n");
    printf("\033[0m");

    return 0;
}