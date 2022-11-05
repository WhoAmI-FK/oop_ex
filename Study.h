#pragma once
#include "Courses.h"
#include <map>

namespace __courses {

	class Study {
	public:
		void add(Course&& c)
		{
			_listOfChCourses[c.getCourseName()] = std::move(c);
			_currNumofACourses++;
			if (_currNumofACourses >= _maxNumOfACourses)
			{
				throw LimitError(_maxNumOfACourses);
			}
		}

		void remove(const std::string& courseToRemove)
		{
			if (_listOfChCourses.find(courseToRemove) == _listOfChCourses.end())
			{
				throw NameError(courseToRemove);
			}
			else {
				_listOfChCourses.erase(courseToRemove);
				_currNumofACourses--;
			}
		}
	
		Study(const std::string& name, std::uint8_t yos, std::int32_t max)
			:
			_name(name),
			_yearOfStudy(yos),
			_maxNumOfACourses(max)
		{

		}

		double averageGrade()
		{
			double avg = 0;
			for (auto t = _listOfChCourses.begin(); t != _listOfChCourses.end(); t++)
			{
				avg += (*t).second.getMark();
			}
			return (avg / _currNumofACourses);
		}
		
		class LimitError : std::exception
		{
		public:
			LimitError(std::int32_t mc)
			{
				_mc = mc;
			}
			const char* what() const noexcept override {
				return (std::string("only ") + std::to_string(_mc) + std::string(" allowed")).c_str();
			}
		private:
			std::int32_t _mc;
		};

		class NameError : std::exception
		{
		public:
			NameError(const std::string& mc)
			{
				_mc = mc;
			}
			const char* what() const noexcept override {
				return (_mc + std::string(" doesnt exists")).c_str();
			}
		private:
			std::string _mc;
		};

	private:
		std::uint8_t _yearOfStudy;
		std::string _name;
		std::int32_t _maxNumOfACourses;
		std::int32_t _currNumofACourses;
		std::map<std::string, Course> _listOfChCourses;
	};
}