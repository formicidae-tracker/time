#pragma once

#include <cstdint>
#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>
#include <memory>

#include <google/protobuf/timestamp.pb.h>

/**
 * the fort namespace
 */
namespace fort {

/**
 *  The amount of time ellapsed between two Time.
 *
 * A Duration represents the amount of time between two Time.
 *
 *
 * This class aims to replicate a [go](https://golang.org) syntax. For
 * example to represent one hour, 10 minute, one may write:
 * ```c++
 * using namespace fort;
 * Duration d = 1 * Duration::Hour + 10 * Duration::Minute;
 * ```
 *
 * The bindings allows for the same semantic:
 *
 * For python:
 * ```python
 * import py_fort_myrmidon as fm
 *
 * a = 2*fm.Duration.Minute + 34 * fm.Duration.Second
 * print(a) # will show '2m34s'
 * ```
 *
 * or R:
 * ```R
 * library(FortMyrmidon)
 *
 * a <- fmMinute(2) + fmSecond(34)
 * str(a) # will show '2m34s'
 * ```
 */
class Duration {
public:
	/**
	 * constructor by an ammount of nanosecond
	 *
	 * @param ns the number of nanosecond
	 */
	inline Duration(int64_t ns)
		: d_nanoseconds(ns) {}
	/**
	 * Default constructor with a zero duration.
	 */
	inline Duration()
		: d_nanoseconds(0) {
	}

	/**
	 * constructor from std::chrono::duration
	 *
	 * @tparam T first <std::chrono::duration> template
	 * @tparam U second <std::chrono::duration> template
	 * @param duration the <std::chrono::duration> to convert
	 */
	template <typename T,typename U>
	Duration( const std::chrono::duration<T,U> & duration)
		: d_nanoseconds(std::chrono::duration<int64_t,std::nano>(duration).count()) {}


	/**
	 * Gets the duration in hours
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Duration.Hours(self) -> float
	 * ```
	 * R:
	 * ```R
	 * fmDurationHours <-function(duration) # returns a numerical
	 * ```
	 *
	 * @return the duration in hours
	 */
	double Hours() const;

	/**
	 * Gets the duration in minutes
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Duration.Minutes(self) -> float
	 * ```
	 * R:
	 * ```R
	 * fmDurationMinutes <-function(duration) # returns a numerical
	 * ```
	 *
	 * @return the duration in minutes
	 */
	double Minutes() const;

	/**
	 * Gets the duration in seconds
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Duration.Seconds(self) -> float
	 * ```
	 * R:
	 * ```R
	 * fmDurationSeconds <-function(duration) # returns a numerical
	 * ```
	 *
	 * @return the duration in seconds
	 */
	double Seconds() const;

	/**
	 * Gets the duration in milliseconds
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Duration.Milliseconds(self) -> float
	 * ```
	 * R:
	 * ```R
	 * fmDurationMilliseconds <-function(duration) # returns a numerical
	 * ```
	 *
	 * @return the duration in milliseconds
	 */
	double Milliseconds() const;

	/**
	 * Gets the duration in microseconds
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Duration.Microseconds(self) -> float
	 * ```
	 * R:
	 * ```R
	 * fmDurationMicroseconds <-function(duration) # returns a numerical
	 * ```
	 *
	 * @return the duration in microseconds
	 */
	double Microseconds() const;

	/**
	 * Gets the duration in nanoseconds
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Duration.Nanoseconds(self) -> int
	 * ```
	 * R:
	 * ```R
	 * fmDurationNanoseconds <-function(duration) # returns an integer
	 * ```
	 *
	 * @return the duration in nanoseconds
	 */
	int64_t Nanoseconds() const {
		return d_nanoseconds;
	}

	/**
	 *  Parses a string to a Duration
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Duration.Parse(d :str) -> py_fort_myrmidon.Duration
	 * ```
	 * * R:
	 * ```
	 * fmDurationParse <- function(d = '') # returns a Rcpp_fmDuration
	 * ```

	 * @param d the string to Parse in the form  `"2h"` or `"1m"`
	 *
	 * Parses a std::string to a Duration. string must be of the
	 * form `[amount][unit]` where `[amount]` is a value that may
	 * contain a decimal point, and `[unit]` could be any of `h`, `m`,
	 * `s`, `ms`, `us`, `µs` and `ns`. This pattern may be
	 * repeated. For example `4m32s` is a valid input.
	 *
	 * @throws std::runtime_error if d is an invalid string
	 *
	 * @return the Duration represented by the string.
	 */
	static Duration Parse(const std::string & d);


	/**
	 * The Value for an hour.
	 *
	 * * Python: `py_fort_myrmidon.Duration.Hour` read-only class variable
	 * * R:
	 * ```R
	 * # we use a method to build an hour
	 * fmHour(1)
	 * ```
	 */
	const static Duration Hour;

	/**
	 * The Value for a minute.
	 *
	 * * Python: `py_fort_myrmidon.Duration.Minute` read-only class variable
	 * * R:
	 * ```R
	 * # we use a method to build a minute
	 * fmMinute(1)
	 * ```
	 */
	const static Duration Minute;
	/**
	 * The Value for a second.
	 *
	 * * Python: `py_fort_myrmidon.Duration.Second` read-only class variable
	 * * R:
	 * ```R
	 * # we use a method to build a second
	 * fmSecond(1)
	 * ```
	 */
	const static Duration Second;
	/**
	 * The Value for a millisecond.
	 *
	 * * Python: `py_fort_myrmidon.Duration.Millisecond` read-only class variable
	 * * R:
	 * ```R
	 * # we use a method to build a millisecond
	 * fmMillisecond(1)
	 * ```
	 */
	const static Duration Millisecond;
	/**
	 * The Value for a microsecond.
	 *
	 * * Python: `py_fort_myrmidon.Duration.Microsecond` read-only class variable
	 * * R:
	 * ```R
	 * # we use a method to build a microsecond
	 * fmMicrosecond(1)
	 * ```
	 */
	const static Duration Microsecond;

	/**
	 * The Value for a nanosecond.
	 *
	 * * Python: `py_fort_myrmidon.Duration.Nanosecond` read-only class variable
	 * * R:
	 * ```R
	 * # we use a method to build a nanosecond
	 * fmNanosecond(1)
	 * ```
	 */
	const static Duration Nanosecond;

	/**
	 * The addition operator
	 *
	 * @param other the other Duration to add
	 *
	 * Adds two Duration. Silently overflow following int64_t arithmetic.
	 *
	 * @return a new duration `this + other `
	 */
	inline Duration operator+(const Duration & other) const {
		return d_nanoseconds + other.d_nanoseconds;
	}

	/**
	 * Multiplication operator
	 * @param other the other Duration to multiply.
	 *
	 * Multiplies two Duration.
	 *
	 * @return a new duration `this * other `
	 */
	inline Duration operator*(const fort::Duration & other) const {
		return d_nanoseconds * other.d_nanoseconds;
	}

	/**
	 * Substraction operator
	 * @param other the other Duration to substract
	 *
	 * Substracts two Duration.
	 * @return a new duration `this - other `
	 */
	inline Duration operator-(const fort::Duration & other) const {
		return d_nanoseconds - other.d_nanoseconds;
	}

	/**
	 * Negation operator
	 *
	 * @return the opposite duration `- this`
	 */
	inline Duration operator-() const {
		return -d_nanoseconds;
	}

	/**
	 * Less than operator
	 * @param other the Duration to compare
	 *
	 * Compares two Duration.
	 *
	 * @return `this < other`
	 */
	inline bool operator<( const Duration & other ) const {
		return d_nanoseconds < other.d_nanoseconds;
	}

	/**
	 * Less or equal operator
	 * @param other the Duration to compare
	 *
	 * Compares two Duration.
	 * @return `this <= other`
	 */
	inline bool operator<=( const Duration & other ) const {
		return d_nanoseconds <= other.d_nanoseconds;
	}

	/**
	 * Greater than operator
	 * @param other the Duration to compare
	 *
	 * Compares two Duration.
	 * @return `this > other`
	 */

	inline bool operator>( const Duration & other ) const {
		return d_nanoseconds > other.d_nanoseconds;
	}

	/**
	 * Greater or equal operator
	 * @param other the Duration to compare
	 *
	 * Compares two Duration.
	 * @return `this >= other`
	 */
	inline bool operator>=( const Duration & other ) const {
		return d_nanoseconds >= other.d_nanoseconds;
	}

	/**
	 * Equality operator
	 * @param other the Duration to compare
	 *
	 * Compares two Duration.
	 * @return `this == other`
	 */
	inline bool operator==( const Duration & other ) const {
		return d_nanoseconds == other.d_nanoseconds;
	}


private:
	friend class Time;

	int64_t d_nanoseconds;
};


/**
 *  A point in time
 *
 * Time represents a point in time in UTC timezone
 *
 * why not std::chrono::time_point ?
 * =================================

 * Why re-implementing one of this object and not using a `struct
 * timeval` or a `std::chrono` ? We are dealing with long living
 * experiment on heterogenous systems. Under this circunstances, we
 * would like also to measure precise time difference. For this
 * purpose we could use the framegrabber monolotic clock, which is
 * timestamping every frame we acquired.
 *
 * Well the issue is that we cannot solely rely on this clock, as we
 * may have several computers each with their own monolithic clock. Or
 * even with a single computer, every time we starts the tracking we
 * must assume a new monotonic clock.
 *
 * We could use the wall clock but this clock may be resetted any
 * time, and we would end up with issue where a time difference
 * between two consecutive frames could be negative. This happen
 * during leap seconds.
 *
 * Inspired from golang [time.Time](https: *golang.org/pkg/time#Time)
 * we propose an Object that store both a Wall time, and a Monotonic
 * timestamp. But here we could have different monotonic timestamp
 * issued by different monotonic clocks. We try, whenever its possible
 * use monotonic value for time differences and comparisons. It could
 * only be the case if both object have a MonotonicValue() issued from
 * the same clock. Otherwise the Wall clock value will be used with
 * the issue regarding the jitter or Wall clock reset.
 *
 * Differentiaing Monotonic clock is done through MonoclockID()
 * values. The 0 value is reserved for the #SYSTEM_MONOTONIC_CLOCK and
 * which is used by Now(). When reading saved monotonic Timestamp from
 * the filesystem (as it is the case when reading data from different
 * `TrackingDataDirectory` ), care must be taken to assign different
 * MonoclockID() for each of those reading. This class does not
 * enforce any mechanism. The only entry point to define the
 * MonoclockID() is through the utility function
 * FromTimestampAndMonotonic().
 *
 * Every time are considered UTC.
 *
 */
class Time {
public:
	/**
	 * Time values can overflow when performing operation on them.
	 */
	class Overflow : public std::runtime_error {
	public:
		/**
		 * Construct an overflow from a clocktype name
		 * @param clocktype the clock type to use
		 */
		Overflow(const std::string & clocktype)
			: std::runtime_error(clocktype + " value will overflow") {}
		/**
		 * default destructor
		 */
		virtual ~Overflow() {}
	};

	/**
	 * ID for a Monotonic Clock
	 */
	typedef uint32_t MonoclockID;

	/**
	 * Returns the positive infinite Time
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Time.Forever() -> py_fort_myrmidon.Time
	 * ```
	 * * R:
	 * ```R
	 fmTimeForever <- function() # returns a Rcpp_fmTime
	 * ```
	 *
	 * Returns the positive infinite Time. For any other Time value,
	 * Before() will return `true`. Any computation with this value will
	 * Overflow. Calling this method is the only to construct such
	 * Time, as operation on other regular Time will Overflow
	 * before.
	 *
	 *
	 * @return a positive infinite Time
	 */
	static Time Forever();

	/**
	 * Returns the negative infinite Time
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Time.SinceEver() -> py_fort_myrmidon.Time
	 * ```
	 * * R:
	 * ```R
	 fmTimeSinceEver <- function() # returns a Rcpp_fmTime
	 * ```
	 *
	 * Returns the negative infinite Time. For any other Time value,
	 * After() will return `true`. Any computation with this value will
	 * Overflow. Calling this method is the only to construct such
	 * Time, as operation on other regular Time will Overflow
	 * before.
	 *
	 * @return a negative infinite Time
	 */
	static Time SinceEver();

	/**
	 * Gets the current Time
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Time.Now() -> py_fort_myrmidon.Time
	 * ```
	 * * R:
	 * ```R
	 fmTimeNow <- function() # returns a Rcpp_fmTime
	 * ```
	 *
	 * Gets the current Time. This time will both have a wall and a
	 * monotonic clock reading associated with the
	 * #SYSTEM_MONOTONIC_CLOCK. Therefore such idioms:
	 *
	 * ```c++
	 * auto start = fort::Time::Now();
	 * SomeFunction();
	 * auto ellapsed = fort::Time::Now().Sub(start);
	 * ```
	 *
	 * Will always return a positive Duration, even if the wall clock
	 * has been reset between the two calls to Now()
	 *
	 *
	 * @return the current <myrmidon::Time>
	 */
	static Time Now();

	/**
	 * Creates a Time from `time_t`
	 * @param t the time_t value
	 *
	 * \note this method have no python or R binding
	 *
	 * The Time will not have any monotonic clock value.
	 *
	 * @return the converted Time
	 */
	static Time FromTimeT(time_t t);


	/**
	 * Creates a Time from `struct timeval`
	 * @param t the `struct timeval`
	 *
	 * \note this method have no python or R binding
	 *
	 * The Time will not have any monotonic clock value.
	 *
	 * @return the converted Time
	 */
	static Time FromTimeval(const timeval & t);

	/**
	 * Creates a Time from a protobuf Timestamp
	 * @param timestamp the `google.protobuf.Timestamp` message
	 *
	 * \note this method have no python or R binding
	 *
	 * The Time will not have any monotonic clock value.
	 *
	 * @return the converted Time
	 */
	static Time FromTimestamp(const google::protobuf::Timestamp & timestamp);


	/**
	 * Creates a Time from Unix EPOCH
	 * @param seconds number of seconds since 1970-01-01T00:00:00.000Z
	 * @param nanoseconds reminder of seconds since 1970-01-01T00:00:00.000Z
	 *
	 * \note this method have no python or R binding
	 *
	 * @return the corresponding Time
	 */
	static Time FromUnix(int64_t seconds,
	                     int32_t nanoseconds);

	/**
	 * Creates a Time from a protobuf Timestamp and an external Monotonic clock
	 * @param timestamp the `google.protobuf.Timestamp` message
	 * @param nsecs the external monotonic value in nanoseconds
	 * @param monoID the external monoID
	 *
	 * \note this method have no python or R binding
	 *
	 * Creates a Time from a protobuf Timestamp and an
	 * external monotonic clock. The two values should correspond to
	 * the same physical time. It is an helper function to create
	 * accurate Time from data saved in
	 * `fort.hermes.FrameReadout` protobuf messages that saves both a
	 * Wall time value and a framegrabber timestamp for each frame. It
	 * is the caller responsability to manage monoID values for not
	 * mixing timestamp issued from different clocks. Nothing prevent
	 * you to use #SYSTEM_MONOTONIC_CLOCK for the monoID value but
	 * the behavior manipulating resulting times is undefined.
	 *
	 * @return the converted Time with associated
	 *         monotonic data
	 */
	static Time FromTimestampAndMonotonic(const google::protobuf::Timestamp & timestamp,
	                                      uint64_t nsecs,
	                                      MonoclockID monoID);

	/**
	 * Parses from RFC 3339 date string format.
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Time.Parse(input: str) -> py_fort_myrmidon.Time
	 * ```
	 * * R:
	 * ```R
	 fmTimeParse <- function(input = '') # returns a Rcpp_fmTime
	 * ```
	 *
	 * @param input the string to parse
	 *
	 * Parses from [RFC 3339](https: *www.ietf.org/rfc/rfc3339.txt)
	 * date string format, i.e. string of the form
	 * `1972-01-01T10:00:20.021-05:00`. It is merely a wrapper from
	 * google::protobuf::time_util functions.
	 *
	 *
	 * @throws std::exception if input is not a RFC 3339 valid string
	 *
	 * @return the converted <myrmidon::Time>
	 */
	static Time Parse(const std::string & input);

	/**
	 * Converts to a `time_t`
	 *
	 * \note this method have no python or R binding
	 *
	 * @return `time_t`representing the Time.
	 */
	time_t ToTimeT() const;

	/**
	 * Converts to a `struct timeval`
	 *
	 * \note this method have no python or R binding
	 *
	 * @return `struct timeval`representing the Time.
	 */
	timeval ToTimeval() const;

	/**
	 * Converts to a protobuf Timestamp message
	 *
	 * \note this method have no python or R binding
	 *
	 * @return the protobuf Timestamp representing the Time.
	 */
	google::protobuf::Timestamp ToTimestamp() const;

	/**
	 * In-place conversion to a protobuf Timestamp
	 *
	 * \note this method have no python or R binding
	 *
	 * @param timestamp the timestamp to modify to represent the Time
	 */
	void ToTimestamp(google::protobuf::Timestamp * timestamp) const;

	/**
	 * Default constructor
	 *
	 * * Python: `py_fort_myrmidon.__init__(self)`
	 * * R: `fmTime <- function() # return a Rcpp_fmTime`
	 *
	 * \note this method have no R binding
	 *
	 * The resulting Time will represent the epoch.
	 */
	explicit Time();

	/**
	 * Adds a Duration to a Time
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Time.Add(self,input: py_fort_myrmidon.Duration) -> py_fort_myrmidon.Time
	 * ```
	 * * R:
	 * ```R
	 * fmTimeAdd <- function(time,duration = fmSecond(0.0)) # returns a Rcpp_fmTime
	 * ```
	 *
	 * @param d the Duration to add
	 *
	 * @return a new Time distant by d from this Time
	 *
	 * @throws Overflow if the computation will go over the minimal or
	 *         maximal representable Time.
	 */
	Time Add(const Duration & d) const;

	/**
	 * Rounds a Time to a Duration
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Time.Round(self,duration: py_fort_myrmidon.Duration) -> py_fort_myrmidon.Time
	 * ```
	 * * R:
	 * ```R
	 * fmTimeRound <- function(time,duration = fmSecond(1.0)) # returns a Rcpp_fmTime
	 * ```
	 *
	 * @param d the Duration to round to.
	 *
	 * Rounds the Time to the half-rounded up Duration d. Currently
	 * only multiple of Duration::Second and power of 10 of
	 * Duration::Nanosecond which are smaller than a second are
	 * supported.
	 *
	 *
	 * @return a new Time rounded to the wanted duration
	 */
	Time Round(const Duration & d) const;

	/**
	 * Gets the Reminder of the division by a Duration
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Time.Reminder(self,duration: py_fort_myrmidon.Duration) -> py_fort_myrmidon.Duration
	 * ```
	 * * R:
	 * ```R
	 * fmTimeReminder <- function(time,duration = fmSecond(1.0)) # returns a Rcpp_fmDuration
	 * ```
	 *
	 * @param d the Duration to divide by
	 *
	 * Finds the Duration which remains if this Time would be
	 * divided by d. Only multiple of Duration::Second or power of
	 * 10 of Duration::Nanosecond smaller than a second are
	 * supported.
	 *
	 * @return a Duration that would remain if this Time would be
	 *         divided by d
	 */
	Duration Reminder(const Duration & d) const;

	/**
	 * Reports if this time is after t
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Time.After(self,time: py_fort_myrmidon.Time) -> bool
	 * ```
	 * * R: this function has no binding in R, use comparison operators
	 *
	 * @param t the Time to test against
	 *
	 * @return `true` if this Time is strictly after t
	 */
	bool After(const Time & t) const;

	/**
	 * Reports if this time is before t
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Time.Before(self,time: py_fort_myrmidon.Time) -> bool
	 * ```
	 * * R: this function has no binding in R, use comparison operators
	 *
	 * @param t the Time to test against
	 *
	 * @return `true` if this Time is strictly before t
	 */
	bool Before(const Time & t) const;

	/**
	 * Reports if this time is the same than t 	 * * Python:
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Time.Equals(self,time: py_fort_myrmidon.Time) -> bool
	 * ```
	 * * R:
	 * ```R
	 * fmTimeEquals <- function(t1,t2) # returns a logical
	 * ```
	 *
	 * @param t the Time to test against
	 *
	 *
	 * @return `true` if this Time> is the same than t
	 */
	bool Equals(const Time & t) const;

	/**
	 * Reports if this Time is +∞
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Time.IsForever(self) -> bool
	 * ```
	 * * R:
	 * ```R
	 * fmTimeIsForever <- function(t1) # returns a logical
	 * ```
	 *
	 * @return true if this Time is Forever()
	 */
	bool IsForever() const;

	/**
	 * Reports if this Time is -∞
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Time.IsSinceEver(self) -> bool
	 * ```
	 * * R:
	 * ```R
	 * fmTimeIsSinceEver <- function(time) # returns a logical
	 * ```
	 *
	 * @return true if this Time is SinceEver()
	 */
	bool IsSinceEver() const;

	/**
	 * Reports if this Time is either Forever or SinceEver.
	 *
	 * * Python:
	 *```python
	 * py_fort_myrmidon.Time.IsInfinite(self) -> bool
	 * ```
	 * * R:
	 * ```R
	 * fmTimeIsInfinite <- function(time) # returns a logical
	 * ```
	 *
	 * @return true if this Time is Forever() or SinceEver().
	 */
	bool IsInfinite() const;

	/**
	 * Computes time difference with another time.
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Time.Sub(self, time: py_fort_myrmidon.Time) -> py_fort_myrmidon.Duration
	 * ```
	 * * R: this function has no binding, use the minus operator on both time.
	 *
	 * @param t the Time to substract to this one.
	 *
	 * @return a Duration representing the time ellapsed between
	 *         `this` and t. It could be negative.
	 *
	 * @throws Overflow if the time Differance is larger than a signed
	 *         64-bit amount of nanoseconds.
	 */
	Duration Sub(const Time & t) const;

	/**
	 * The current system monotonic clock.
	 *
	 * \note this method have no python or R binding.
	 *
	 * The MonoclockID reserved for the current system ( aka
	 * `CLOCK_MONOTONIC`).
	 */
	const static MonoclockID SYSTEM_MONOTONIC_CLOCK = 0;

	/**
	 * Reports the presence of a monotonic time value.
	 *
	 * \note this method have no python or R binding.
	 *
	 * Reports the presence of a monotonic time value. Only
	 * Time issued by Now() or FromTimestampAndMonotonic()
	 * contains a monotonic time value.
	 *
	 * @return `true` if `this` contains a monotonic clock value.
	 */
	bool HasMono() const;

	/**
	 * Gets the referred MonoclockID.
	 *
	 * \note this method have no python or R binding.
	 *
	 * @return the MonoclockID designating the monotonic clock the
	 *         monotonic time value refers to.
	 *
	 * @throws std::exception if this Time has no monotonic clock value.
	 */
	MonoclockID MonoID() const;

	/**
	 * Gets the monotonic value.
	 *
	 * \note this method have no python or R binding.
	 *
	 * @return the monotonic clock value.
	 *
	 * @throws std::exception if this Time has no monotonic clock
	 * value.
	 */
	uint64_t MonotonicValue() const;

	/**
	 * Formats the Time as a RFC 3339 string.
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Time.__str__(self) -> str
	 * ```
	 * * R:
	 * ```R
	 * fmTimeFormat <- function(time) # returns a character
	 * `show.Rcpp_fmTime` <- function(time)
	 * ```
	 *
	 * @return a string representing this Time. Either using RFC 3339
	 *         or +/-∞ if this Time::IsInfinite()
	 */
	std::string Format() const;

	/**
	 * Builds a debug string
	 *
	 * * Python:
	 * ```python
	 * py_fort_myrmidon.Time.__repr__(self) -> str
	 * ```
	 * * R:
	 * ```R
	 * ```
	 *
	 * This method is useful for internal debugging. Prefer the
	 * standard c++ formatting operator on std::ostream or Format().
	 *
	 * @return a debug string with the complete time internal state.
	 */
	std::string DebugString() const;

	/**
	 * Helpers to convert (sec,nsec) to nsec
	 * @param sec the amount of second
	 * @param nsec the amount of nanos
	 *
	 * \note this method has no python or R bindings
	 *
	 * @throws Overflow
	 *
	 * @return sec * 1e9 + nsec if no overflow
	 */
	static uint64_t MonoFromSecNSec(uint64_t sec, uint64_t nsec);

	/**
	 * Equal comparison operator
	 * @param other the other Time to compare to
	 *
	 * @return `true` if `this == other`
	 */
	inline bool operator == (const Time & other ) const  {
		return Equals(other);
	}

	/**
	 * Less than operator
	 * @param other the other Time to compare to
	 *
	 * @return `true` if `this < other`
	 */
	inline bool operator < (const Time & other ) const  {
		return Before(other);
	}

	/**
	 * Less or equal operator
	 * @param other the other Time to compare to
	 *
	 * @return `true` if `this <= other`
	 */
	inline bool operator <= (const Time & other ) const  {
		return !other.Before(*this);
	}

	/**
	 * Greater than operator
	 * @param other the other Time to compare to
	 *
	 * @return `true` if `this > other`
	 */
	inline bool operator > (const Time & other ) const  {
		return other.Before(*this);
	}

	/**
	 * Greate or equal operator
	 * @param other the other Time to compare to
	 *
	 * @return `true` if `this >= other`
	 */
	inline bool operator >= (const Time & other ) const  {
		return !Before(other);
	}

private:

	// Number of nanoseconds in a second.
	const static uint64_t NANOS_PER_SECOND = 1000000000ULL;

	// Number of nanoseconds in a millisecond.
	const static uint64_t NANOS_PER_MILLISECOND = 1000000ULL;
	// Number of nanoseconds in a microsecond.
	const static uint64_t NANOS_PER_MICROSECOND = 1000ULL;

	Time(int64_t wallsec, int32_t wallnsec, uint64_t mono, MonoclockID ID);


	const static uint32_t HAS_MONO_BIT = 0x80000000ULL;
	int64_t     d_wallSec;
	int32_t     d_wallNsec;
	uint64_t    d_mono;
	MonoclockID d_monoID;
};

}  // namespace fort


/**
 * Operator for fort::myrmidon::Duration multiplication
 * @param a a signed integer
 * @param b the Duration to multiply
 *
 * @return `a*b`
 */
inline fort::Duration operator*(int64_t a,
                                const fort::Duration & b) {
	return a * b.Nanoseconds();
}


/**
 * Formats a Duration
 * @param out the std::ostream to format to
 * @param d the fort::Duration to format
 *
 * Formats the Duration to the form
 * "1h2m3.4s". Leading zero unit are omitted, and unit smaller than 1s
 * uses a smalle unit ms us or ns. The zero duration formats to 0s. It
 * mimic golang's
 * [time.Duration.String()](https: *golang.org/pkg/time/#Duration.String)
 * behavior.
 *
 * @return a reference to out
 */
std::ostream & operator<<(std::ostream & out,
                          const fort::Duration & d);

/**
 * Formats Time to RFC 3339 date string format
 * @param out the output iostream
 * @param t the fort::Time to format
 *
 * Formats to [RFC 3339](https: *www.ietf.org/rfc/rfc3339.txt) date
 * string format, i.e. string of the form
 * `1972-01-01T10:00:20.021Z`. It is merely a wrapper from
 * google::protobuf::time_util functions.
 *
 * @return a reference to out
 */
std::ostream & operator<<(std::ostream & out,
                          const fort::Time & t);
