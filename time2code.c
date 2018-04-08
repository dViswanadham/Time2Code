// time2code.c
// Assignment 1, COMP1511 18s1: Time To Code.
//
// This program by Dheeraj Viswanadham (z5204820) 
// Start: 27/03/18 | Last edited: 8/04/18
// Version update: 28/03/18
// Version 1.0.2: Add version numbers and header comment. 
// Version 1.0.1: Fix day/time variable mix-up in main function.
// Version 1.0.0: Assignment released.

#include <stdio.h>
#include <assert.h>

// You must use these #defines - DO NOT CHANGE THEM

#define TOWN_ADELAIDE       0  // ACDT 
#define TOWN_BRISBANE       1  // Daylight savings not observed i.e. only AEST
#define TOWN_BROKEN_HILL    2  // ACDT
#define TOWN_CANBERRA       3  // AEDT
#define TOWN_DARWIN         4  // Daylight savings not observed i.e. only ACST
#define TOWN_EUCLA          5  // Daylight savings not observed i.e. only ACWST
#define TOWN_HOBART         6  // AEDT
#define TOWN_LORD_HOWE_IS   7  // LHDT
#define TOWN_MELBOURNE      8  // AEDT
#define TOWN_PERTH          9  // Daylight savings not observed i.e. AWST
#define TOWN_SYDNEY         10  // AEDT

// New Zealand

#define TOWN_AUCKLAND       11  // NZDT
#define TOWN_CHRISTCHURCH   12  // NZDT
#define TOWN_WELLINGTON     13  // NZDT

// Australia Daylight savings starts 1/10/17 (October) at 2am i.e. 158, 159, 300
//         and it ends on 1/04/18 (April) at 2am i.e. 158, 159, 100.
//         It then starts again on 7/10/18 at 2am finishing on 7/04/19 at 2am.           
// I.e. When local daylight time was about to reach
// Sunday, 1 April 2018, 3:00:00 am clocks were turned backward 1 hour to 
// Sunday, 1 April 2018, 2:00:00 am local standard time instead.

#define TIMEZONE_AWST_OFFSET  800 // Australian Western Standard Time

#define TIMEZONE_ACWST_OFFSET 845 // Australian Central Western Standard Time

#define TIMEZONE_ACST_OFFSET  930 // Australian Central Standard Time
#define TIMEZONE_ACDT_OFFSET 1030 // Australian Central Daylight Time i.e. +1hr 

#define TIMEZONE_AEST_OFFSET 1000 // Australian Eastern Standard Time
#define TIMEZONE_AEDT_OFFSET 1100 // Australian Eastern Daylight Time i.e. +1hr

#define TIMEZONE_LHST_OFFSET 1030 // Lord Howe Standard Time
#define TIMEZONE_LHDT_OFFSET 1100 // Lord Howe Daylight Time i.e. +30mins

// New Zealand Daylight savings starts 24/09/17 (October) at 2am- 158, 159, 300
//         and it ends on 1/04/18 (April) at 2am i.e. 158, 159, 100. 
//         It then starts again on 30/09/18 at 2am finishing on 7/04/19 at 2am.
// I.e. When local daylight time was about to reach
// Sunday, 1 April 2018, 3:00:00 am clocks were turned backward 1 hour to 
// Sunday, 1 April 2018, 2:00:00 am local standard time instead.

#define TIMEZONE_NZST_OFFSET 1200 // NZ Standard Time
#define TIMEZONE_NZDT_OFFSET 1300 // NZ Daylight Time i.e. +1hr

// returned by get_local_time
#define INVALID_INPUT (-1)


// ADD YOUR #defines (if any) here
#define N_TOWN 14

#define UTC_ACST_START 1630 // MAR 31
#define UTC_ACDT_START 1630 	// OCT 6 
#define UTC_AEST_START 1600 // MAR 31
#define UTC_AEDT_START 1600 	// OCT 6 
#define UTC_LHST_START 1500 // MAR 31
#define UTC_LHDT_START 1530 	// OCT 6 
#define UTC_NZST_START 1400 // MAR 31
#define UTC_NZDT_START 1400 	// SEP 29

#define JAN 1
#define FEB 2
#define MAR 3
#define APR 4
#define MAY 5
#define JUN 6
#define JUL 7
#define AUG 8
#define SEP 9
#define OCT 10
#define NOV 11
#define DEC 12

#define MIN_DAYS 1
#define MAX_DAYS_FEB 28 // February
#define MAX_DAYS_APR_JUN_SEP_NOV 30 // April+June+September+November
#define MAX_DAYS_GENERAL 31 // Jan+Mar+May+Jul+Aug+Oct+Dec

#define MIN_TIME 0
#define MAX_TIME 2359
#define HOUR 100
#define DAY 2400
#define MAX_MINUTE 59
#define INVALID_HOUR 24




int get_local_time(int town, int utc_month, int utc_day, int utc_time);
void run_unit_tests(void);


// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE
int call_invalid(int town, int utc_month, int utc_day, int utc_time);
int calc_local_time(int local_time);


// DO NOT CHANGE THIS FUNCTION

// This main function won't be marked as part of the assignment
// It tests the functions you have to write.
// Do not change this main function.  If it does not work with
// your functions you have misunderstood the assignment.

int main(void) {
    int call_get_local_time = 0;

    printf("Enter 0 to call run_unit_tests()\n");
    printf("Enter 1 to call get_local_time()\n");
    printf("Call which function: ");
    scanf("%d", &call_get_local_time);

    if (!call_get_local_time) {
        printf("calling run_unit_tests()\n");
        run_unit_tests();
        printf("unit tests done\n");
        return 0;
    }

    int town = 0;
    int month = 0;
    int day = 0;
    int time = 0;

    printf("Enter %d for Adelaide\n", TOWN_ADELAIDE);
    printf("Enter %d for Brisbane\n", TOWN_BRISBANE);
    printf("Enter %d for Broken_hill\n", TOWN_BROKEN_HILL);
    printf("Enter %d for Canberra\n", TOWN_CANBERRA);
    printf("Enter %d for Darwin\n", TOWN_DARWIN);
    printf("Enter %d for Eucla\n", TOWN_EUCLA);
    printf("Enter %d for Hobart\n", TOWN_HOBART);
    printf("Enter %d for Lord Howe Island\n", TOWN_LORD_HOWE_IS);
    printf("Enter %d for Melbourne\n", TOWN_MELBOURNE);
    printf("Enter %d for Perth\n", TOWN_PERTH);
    printf("Enter %d for Sydney\n", TOWN_SYDNEY);
    printf("Enter %d for Auckland\n", TOWN_AUCKLAND);
    printf("Enter %d for Christchurch\n", TOWN_CHRISTCHURCH);
    printf("Enter %d for Wellington\n", TOWN_WELLINGTON);

    printf("Which town: ");
    scanf("%d", &town);

    printf("Enter UTC month as integer 1..12: ");
    scanf("%d", &month);

    printf("Enter UTC day as integer 1..31: ");
    scanf("%d", &day);

    printf("Enter UTC time as hour * 100 + minutes\n");
    printf("Enter UTC time as integer [0..2359]: ");
    scanf("%d", &time);

    int local_time = get_local_time(town, month, day, time);

    if (local_time == INVALID_INPUT) {
        printf("invalid input - local time could not be calculated\n");
    } else {
        printf("local_time is %d\n", local_time);
    }
    return 0;
}



// Given an Australian town and a 2018 UTC time
// return the local time in the Australian town
//
// time is returned as hours*100 + minutes
// INVALID_INPUT is return for invalid inputs
//
// utc_month should be 1..12
// utc_day should be 1..31
// utc_time should be 0..2359
// utc_time is hours*100 + minutes
//
// note UTC year is assumed to be 2018
// note UTC seconds is assumed to be zero
//

int get_local_time(int town, int utc_month, int utc_day, int utc_time) {
    int time = 0;
    int local_time = calc_local_time(time);
	
	// CHANGE THIS FUNCTION
    // YOU ARE NOT PERMITTED TO USE ARRAYS, LOOPS, PRINTF OR SCANF
    // SEE THE ASSIGNMENT SPECIFICATION FOR MORE RESTRICTIONS
	
	
	
	
    return local_time;
}


// ADD YOUR FUNCTIONS HERE

// Testing for INVALID_INPUT within the functions:
int call_invalid(int town, int utc_month, int utc_day, int utc_time) {
	int output = 0;
	int utc_hour = utc_time/HOUR;
	int utc_minute = utc_time%HOUR;
	
	if (town < 0 || town >= N_TOWN) {
	    output == INVALID_INPUT;
	}
	else if (utc_month < JAN || utc_month > DEC) {
		output == INVALID_INPUT;
	}
	else if (utc_month == JAN || utc_month == MAR || utc_month == MAY 
	|| utc_month == JUL || utc_month == AUG || utc_month == OCT 
	|| utc_month == DEC) {
		if (utc_day < MIN_DAYS || utc_day > MAX_DAYS_GENERAL) {
			output == INVALID_INPUT;
		}
	}
	else if (utc_month == FEB) {
		if (utc_day < MIN_DAYS || utc_day > MAX_DAYS_FEB) {
			output == INVALID_INPUT;
		}
	}
	else if (utc_month == APR || utc_month == JUN || utc_month == SEP 
	|| utc_month == NOV) {
		if (utc_day < MIN_DAYS || utc_day > MAX_DAYS_APR_JUN_SEP_NOV) {
			output == INVALID_INPUT;
		}
	}
	else if (utc_time < MIN_TIME || utc_time > MAX_TIME 
	|| utc_minute > MAX_MINUTE || utc_hour >= INVALID_HOUR) {
		output == INVALID_INPUT;
	}
	return output;
}

int calc_local_time(int local_time) {
    int month = 0, day = 0, time = 0, utc_town = 0;
	int town = call_town(utc_town);
	int utc_month = call_utc_month(month);
	int utc_day = call_utc_day(day);
	int utc_time = calc_utc_time(time);

// Australian towns:
	// Town = Adelaide/Broken Hill:
	if (town == TOWN_ADELAIDE || town == TOWN_BROKEN_HILL) {
		if (utc_month < MAR) {
			local_time = utc_time + TIMEZONE_ACDT_OFFSET;
		}
		// consider edge cases
		else if (utc_month == MAR) {
			if ((utc_day == MAX_DAYS_GENERAL) && (utc_time >= UTC_ACST_START)) { 
				local_time = utc_time + TIMEZONE_ACST_OFFSET;
			}
			else {
				local_time = utc_time + TIMEZONE_ACDT_OFFSET;
			}
		}
		else if ((utc_month > MAR) && (utc_month < OCT)) {
			local_time = utc_time + TIMEZONE_ACST_OFFSET;
		}
		// consider edge cases
		else if (utc_month == OCT) {
			if (utc_day == 6) {
				if (utc_time >= UTC_ACDT_START) {
					local_time = utc_time + TIMEZONE_ACDT_OFFSET;
				}
				else {
					local_time = utc_time + TIMEZONE_ACST_OFFSET;
				}
			}
			else if (utc_day > 6) {
				local_time = utc_time + TIMEZONE_ACDT_OFFSET;
			}
			else {
				local_time = utc_time + TIMEZONE_ACST_OFFSET;
			}
		}
		else if (utc_month > OCT) {
			local_time = utc_time + TIMEZONE_ACDT_OFFSET;
		}
		else {
			local_time = INVALID_INPUT;
		}
	}
	
	// Town = Brisbane:
	else if (town == TOWN_BRISBANE) {
		if ((utc_month >= JAN) && (utc_month <= DEC)) {
			local_time = utc_time + TIMEZONE_AEST_OFFSET;
		}
		else {
			local_time = INVALID_INPUT;
		}
	}
	
	// Town = Canberra/Hobart/Melbourne/Sydney
	else if (town == TOWN_CANBERRA || town == TOWN_HOBART || 
	town == TOWN_MELBOURNE || town == TOWN_SYDNEY) {
		if (utc_month < MAR) {
			local_time = utc_time + TIMEZONE_AEDT_OFFSET;
		}
		// consider edge cases
		else if (utc_month == MAR) {
			if ((utc_day == MAX_DAYS_GENERAL) && (utc_time >= UTC_AEST_START)) { 
				local_time = utc_time + TIMEZONE_AEST_OFFSET;
			}
			else {
				local_time = utc_time + TIMEZONE_AEDT_OFFSET;
			}
		}
		else if ((utc_month > MAR) && (utc_month < OCT)) {
			local_time = utc_time + TIMEZONE_AEST_OFFSET;
		}
		// consider edge cases
		else if (utc_month == OCT) {
			if (utc_day == 6) {
				if (utc_time >= UTC_AEDT_START) {
					local_time = utc_time + TIMEZONE_AEDT_OFFSET;
				}
				else {
					local_time = utc_time + TIMEZONE_AEST_OFFSET;
				}
			}
			else if (utc_day > 6) {
				local_time = utc_time + TIMEZONE_AEDT_OFFSET;
			}
			else {
				local_time = utc_time + TIMEZONE_AEST_OFFSET;
			}
		}
		else if (utc_month > OCT) {
			local_time = utc_time + TIMEZONE_AEDT_OFFSET;
		}
		else {
			local_time = INVALID_INPUT;
		}
	}
	
	// Town = Darwin:
	else if (town == TOWN_DARWIN) {
		if ((utc_month >= JAN) && (utc_month <= DEC)) {
			local_time = utc_time + TIMEZONE_ACST_OFFSET;
		}
		else {
			local_time = INVALID_INPUT;
		}
	}
	
	// Town = Eucla:
	else if (town == TOWN_EUCLA) {
		if ((utc_month >= JAN) && (utc_month <= DEC)) {
			local_time = utc_time + TIMEZONE_ACWST_OFFSET;
		}
		else {
			local_time = INVALID_INPUT;
		}
	}
	
	// Town = Lord Howe Island:
	else if (town == TOWN_LORD_HOWE_IS) {
		if (utc_month < MAR) {
			local_time = utc_time + TIMEZONE_LHDT_OFFSET;
		}
		// consider edge cases
		else if (utc_month == MAR) {
			if ((utc_day == MAX_DAYS_GENERAL) && (utc_time >= UTC_LHST_START)) { 
				local_time = utc_time + TIMEZONE_LHST_OFFSET;
			}
			else {
				local_time = utc_time + TIMEZONE_LHDT_OFFSET;
			}
		}
		else if ((utc_month > MAR) && (utc_month < OCT)) {
			local_time = utc_time + TIMEZONE_LHST_OFFSET;
		}
		// consider edge cases
		else if (utc_month == OCT) {
			if (utc_day == 6) {
				if (utc_time >= UTC_LHDT_START) {
					local_time = utc_time + TIMEZONE_LHDT_OFFSET;
				}
				else {
					local_time = utc_time + TIMEZONE_LHST_OFFSET;
				}
			}
			else if (utc_day > 6) {
				local_time = utc_time + TIMEZONE_LHDT_OFFSET;
			}
			else {
				local_time = utc_time + TIMEZONE_LHST_OFFSET;
			}
		}
		else if (utc_month > OCT) {
			local_time = utc_time + TIMEZONE_LHDT_OFFSET;
		}
		else {
			local_time = INVALID_INPUT;
		}
	}
	
	// Town = Perth:
	else if (town == TOWN_PERTH) {
		if ((utc_month >= JAN) && (utc_month <= DEC)) {
			local_time = utc_time + TIMEZONE_AWST_OFFSET;
		}
		else {
			local_time = INVALID_INPUT;
		}
	}
	
// New Zealand towns:
	// Town = Auckland/Christchurch/Wellington:
	else if (town == TOWN_AUCKLAND || town == TOWN_CHRISTCHURCH || 
	town == TOWN_WELLINGTON) {
		if (utc_month < MAR) {
			local_time = utc_time + TIMEZONE_NZDT_OFFSET;
		}
		// consider edge cases
		else if (utc_month == MAR) {
			if ((utc_day == MAX_DAYS_GENERAL) && (utc_time >= UTC_NZST_START)) { 
				local_time = utc_time + TIMEZONE_NZST_OFFSET;
			}
			else {
				local_time = utc_time + TIMEZONE_NZDT_OFFSET;
			}
		}
		else if ((utc_month > MAR) && (utc_month < SEP)) {
			local_time = utc_time + TIMEZONE_NZST_OFFSET;
		}
		// consider edge cases
		else if (utc_month == SEP) {
			if (utc_day == 29) {
				if (utc_time >= UTC_NZDT_START) {
					local_time = utc_time + TIMEZONE_NZDT_OFFSET;
				}
				else {
					local_time = utc_time + TIMEZONE_NZST_OFFSET;
				}
			}
			else if (utc_day > 29) {
				local_time = utc_time + TIMEZONE_NZDT_OFFSET;
			}
			else {
				local_time = utc_time + TIMEZONE_NZST_OFFSET;
			}
		}
		else if (utc_month > SEP) {
			local_time = utc_time + TIMEZONE_NZDT_OFFSET;
		}
		else {
			local_time = INVALID_INPUT;
		}
	}

	else {
		return INVALID_INPUT;
	}
	
	if (local_time > MAX_TIME) {
		local_time = (local_time % DAY);
	}
	return local_time;
}

// ADD A COMMENT HERE EXPLAINING YOUR OVERALL TESTING STRATEGY 

// I first decided to draw out a tree diagram with several sub-functions acting
// out as branches. I then determined what an invalid input would be for within 
// each sub-function (such as towns, months, days, etc) and then called these
// sub-functions into a larger calc_local_time function in order to calculate 
// what the local time would be and whether daylight savings applied for that
// given town and time. The below assert cases determine the edge cases for each
// town (if they had DST applied or not) and tested whether they outputted the
// correct times or not, which I double-checked with valid and reliable 
// sources online. 

// run unit tests for get_local_time

void run_unit_tests(void) {
    // 2 example unit tests

    // UTC midnight on 20th March -> time in Sydney: 11am AEDT
    assert(get_local_time(TOWN_SYDNEY, 3, 20, 0) == 1100);

    // 42 is not a valid month
    assert(get_local_time(TOWN_SYDNEY, 42, 0, 0) == INVALID_INPUT);

    // ADD YOUR ASSERT STATEMENTS HERE

    // you should add at least 40 more assert statements to this function
    // with a comment for each test explaining it

    // there should be comment before this function
    // explaining your overall testing strategy
}
