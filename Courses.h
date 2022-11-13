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
		virtual double getMark() {
			return _mark;
		};
		static void setNumOfAvailCourses(int64_t num) {
			_numOfAvailCourses = num;
		};
		static int64_t count()
		{
			return _numOfAvailCourses;
		}

	    std::string getCourseName() const 
		{
			return _name;
		}

		std::string getScienceArea() const
		{
			return _scienceArea;
		}

	protected:
		std::string _name;
		std::string _scienceArea;
		static int64_t _numOfAvailCourses;
		double _mark;
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
	};

	class CheckCourse : public Course
	{
	private:

		template<typename T,typename... Args>
		void calcHelper(std::size_t& nums, T&& t ,Args&&... args)
		{
			if ((typeid(t) == typeid(bool))) {
				if (t) nums++;
				calcHelper(nums, std::forward<Args>(args)...);
			}
			else {
				throw std::runtime_error("Unsupported type...");
			}
		}

		void calcHelper(std::size_t& nums) {};


	public:
		template<class... Args>
		CheckCourse(cStrRef name, cStrRef scienceArea, Args&&... args)
		{
			_name = name;
			_scienceArea = scienceArea;
			const std::size_t size = sizeof...(args);
			if (size != 4)
			{
				throw std::runtime_error("Size has to be equal to 4...");
			}
			std::size_t numOfPos = 0;
			calcHelper(numOfPos,std::forward<Args>(args)...);
			
			switch (numOfPos)
			{
			case 4:
				_mark = 5;
				break;
			case 3:
				_mark = 4;
				break;
			case 2:
				_mark = 3;
				break;
			case 1:
			case 0:
				_mark = 2;
				break;
			default:
				throw std::runtime_error("something strange...");
				break;
			}
			
		}

		// add: copyConst, moveConst, copyOp, moveOp

		double getMark() override {
			return _mark;
		}

		void setMark(const double& mark)
		{
			_mark = mark;
		}
	};
};