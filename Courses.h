#pragma once
#include <string>
#include <stdexcept>
#include <cstdint>

namespace __courses {

	
	class Course
	{
	public:
		virtual ~Course() = default;
	//	virtual void setNumOfAvailCourses()
	//	virtual int64_t getNumOfAvailCourses() = 0;
		virtual double getMark() = 0;
	protected:
		std::string _name;
		std::string _scienceArea;
	//	int64_t _numOfAvailCourses;
	};

	typedef const std::string& cStrRef;
	class ScoredCourse : public Course
	{
	public:
		ScoredCourse(cStrRef name, cStrRef scienceArea, uint32_t scoredMark)
		{
			_name = name;
			_scienceArea = scienceArea;
			
			if (scoredMark <= 49)
				_mark = 2;
			else if (scoredMark <= 59)
				_mark = 3;
			else if (scoredMark <= 69)
				_mark = 3.5;
			else if (scoredMark <= 89)
				_mark = 4;
			else _mark = 5;
		}
		double getMark() override {
			return _mark;
		}
	private:
		double _mark;
	};
	
	class AveragedCourse : public Course
	{
	public:
		AveragedCourse(cStrRef name, cStrRef scienceArea, uint32_t mark1, uint32_t mark2)
		{
		if(mark1 < 0 || mark1 > 5 || mark2 < 0 || mark2 > 5)
		{
			throw std::runtime_error("Mark greater than 5 or less than 0");
		}
			_name = name;
			_scienceArea = scienceArea;

			if (mark1 != 2 && mark2 != 2)
				_mark = (static_cast<double>(mark1) + static_cast<double>(mark2)) / 2;
			else _mark = 2;
		}
		double getMark() override {
			return _mark;
		}
	private:
		double _mark;
	};

	class CheckCourse : public Course
	{
	public:
		CheckCourse(cStrRef name, cStrRef scienceArea, ...)
		{

		}
	};
};