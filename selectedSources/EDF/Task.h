////////////////////////////////////////////////////////////////////////////////
// S.Donchez
// Task.h - header for implementation of the class representing a decryption
// task that the EDF algorithm is scheduling.
////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifdef USE_JSON
#include "nlohmann/json.hpp" //for input parsing
#else
#include "pugixml/pugixml.hpp" //for input parsing
#endif
#include "TimeUnit.h" //Since tasks have time constraints
#include <string> //for taskName
#include <iostream>

/**
 * @brief Implements a decryption task that the EDF algorithm is scheduling.
*/
class Task
{
public:

	/**
	 * @brief The TimeUnit the task needs to be completed by.
	*/
	const TimeUnit* deadline;

	/**
	 * @brief The total number of TimeUnits required to complete the task.
	*/
	const unsigned int unitsToExecute;

	/**
	 * @brief The friendly name of the task, if one is provided, or NULL.
	*/
	const std::string taskName;

	/**
	 * @brief The unique numeric identifier for the task.
	*/
	const unsigned int taskId;

	/**
	 * @brief The frequency with which the task is repeated, or 0 if it is
	 *		  aperiodic. (measured in TimeUnits)
	*/
	const unsigned int period;

	/**
	 * @brief How many units of the task have executed thus far.
	*/
	unsigned int unitsExecuted = 0;

	/**
	 * @brief pointer to the Scheduler's outstandingUnitsToExecute array. This
	 *        class increments the value of the task's deadline's index by
	 *        the value of unitsToExecute at initialization, and decrements
	 *        the same during each time unit it is executed for.
	*/
	int* oUD;

	/**
	 * @brief Constructor for the Task. Assigns values to all of the task
	 *		  properties.
	 * @param deadline		 - The TimeUnit the task needs to be completed by. 
	 * @param unitsToExecute - The total number of TimeUnits required to 
							   complete the task.
	 * @param taskId		 - The unique numeric identifier for the task.
	 * @param taskName		 - The friendly name of the task, if one is 
							   provided, or NULL.
	 * @param period		 - The frequency with which the task is repeated, or
	 *                         0 if it is aperiodic. (measured in TimeUnits).
	 * @param oUD            - A pointer to the scheduler's outstandingUnitsDue
	 *                         array.
	*/
	Task(const TimeUnit* deadline, const unsigned int unitsToExecute, 
		const unsigned int taskId, int oUD[], const std::string taskName = NULL,
		const unsigned int period = 0);

#ifdef USE_JSON
	/**
	 * @brief Constructor for the Task. Assigns values to all of the task
	 *		  properties.
	 * @param deadline - The TimeUnit the task needs to be completed by.
	 * @param task     - A parsed JSON object containing the various
	 *                   attributes of the Task.
	 * @param oUD      - A pointer to the scheduler's outstandingUnitsDue array.
	*/
	Task(const nlohmann::json task, const TimeUnit* deadline, 
		int oUD[]);
#else
	/**
 * @brief Constructor for the Task. Assigns values to all of the task
 *		  properties.
 * @param deadline - The TimeUnit the task needs to be completed by.
 * @param task     - A parsed XML object containing the various
 *                   attributes of the Task.
 * @param oUD      - A pointer to the scheduler's outstandingUnitsDue array.
*/
	Task(const pugi::xml_document* task, const TimeUnit* deadline,
		int oUD[]);
#endif
	/**
	 * @brief Destructor for the Task instance.
	*/
	~Task();

	/**
	 * @brief Determines if a function is periodic or not
	 * @return True if the function is periodic, False otherwise.
	*/
	bool isPeriodic();

	/**
	 * @brief Calculates the number of TimeUnits remaining until the deadline
	 *		  for a given task.
	 * @param CurrentUnit - The TimeUnit to compare against (typically now())
	 * @return number of TimeUnits remaining
	*/
	unsigned int unitsToDeadline(TimeUnit* CurrentUnit);

	/**
	 * @brief Calculates the number of TimeUnits remainig to execute.
	 * @return Number of TimeUnits remaining to execute for the current Task.
	*/
	int unitsRemaining();

	/**
	 * @brief Executes the function for a single TimeUnit. Implementation is
	 *		  target dependent.
	*/
	void executeForTimeUnit();

}; //Task

