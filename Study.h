#pragma once
#include "Courses.h"
#include <map>
#include <iostream>
#include <cstring>

namespace __courses {

	int64_t Course::_numOfAvailCourses;

	class Study {
	public:
		Study() = delete;

		void add(ScoredCourse* c)
		{
			if (_currNumofACourses+1 > _maxNumOfACourses)
			{
				throw LimitError(_maxNumOfACourses);
			}
			_listOfChCourses[(*c).getCourseName()] = std::move(*c);
			_currNumofACourses++;
			Course::setNumOfAvailCourses(_currNumofACourses);
			std::cout << _currNumofACourses << std::endl;
		}
		void add(CheckCourse* c)
		{
			if (_currNumofACourses+1 > _maxNumOfACourses)
			{
				throw LimitError(_maxNumOfACourses);
			}
			_listOfChCourses[(*c).getCourseName()] = std::move(*c);
			_currNumofACourses++;
			Course::setNumOfAvailCourses(_currNumofACourses);
			std::cout << _currNumofACourses << std::endl;
		}

		void add(AveragedCourse* c)
		{
			if (_currNumofACourses+1 > _maxNumOfACourses)
			{
				throw LimitError(_maxNumOfACourses);
			}
			_listOfChCourses[(*c).getCourseName()] = std::move(*c);
			_currNumofACourses++;
			Course::setNumOfAvailCourses(_currNumofACourses);
			std::cout << _currNumofACourses << std::endl;
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
				Course::setNumOfAvailCourses(_currNumofACourses);
			}
		}
	
		Study(const std::string& name, int yos, std::int32_t max)
			:
			_name(name),
			_yearOfStudy(yos),
			_maxNumOfACourses(max),
			_currNumofACourses(0)
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
				arr = nullptr;
			}
			const char* what() const noexcept override {
				std::size_t n = strlen("Only n courses allowed");
				const_cast<LimitError*>(this)->arr = new char[n + 1];
				snprintf(const_cast<LimitError*>(this)->arr, n + 1, "Only %d courses allowed", _mc);
				(const_cast<LimitError*>(this)->arr)[n] = '\0';
				return arr;
			}
			~LimitError()
			{
				if (arr) {
					delete[] arr;
				}
			}
		private:
			char* arr;
			std::int32_t _mc;
		};

		class NameError : std::exception
		{
		public:
			NameError(const std::string& mc)
			{
				_mc = mc;
				arr = nullptr;
			}
			const char* what() const noexcept override {
				std::size_t n = strlen(_mc.c_str()) + strlen(" doesnt exists");
				const_cast<NameError*>(this)->arr = new char[n + 1];
				snprintf(const_cast<NameError*>(this)->arr, n + 1, "%s doesnt exist", _mc.c_str());
				(const_cast<NameError*>(this)->arr)[n] = '\0';
				return arr;
			}
			~NameError()
			{
				if (arr)
				{
					delete[] arr;
				}
			}
		private:
			char* arr;
			std::string _mc;
		};

		class IndexError : std::exception
		{
		public:
			IndexError(const std::size_t& i)
			{
				_li = i;
				arr = nullptr;
			}
			const char* what() const noexcept override {
				std::size_t n = strlen("item no. n not found\n");
				const_cast<IndexError*>(this)->arr = new char[n + 1];
				snprintf(const_cast<IndexError*>(this)->arr, n + 1, "item no. %d not found\n", _li);
				(const_cast<IndexError*>(this)->arr)[n] = '\0';
				return arr;
			}
			~IndexError()
			{
				if (arr)
				{
					delete[] arr;
				}
			}
		private:
			std::size_t _li;
			char* arr;
		};

		Course& operator[](const std::size_t& index)
		{
			if(index < 0 || index >= _listOfChCourses.size())
			{
				throw IndexError(index);
			}
			int times = 0;
			auto t = _listOfChCourses.begin();
			for (std::size_t i = 0; i < index; i++)
			{
				t++;
			}
			return (*t).second;

		}

		std::string getNameOfStudent() const
		{
			return _name;
		}

		int getYearOfStudy() const
		{
			return _yearOfStudy;
		}

		std::int32_t getCurrNumOfACourses() const {
			return _currNumofACourses;
		}

		void clear()
		{
			_listOfChCourses.clear();
			_name = "";
			_maxNumOfACourses = 0;
			_currNumofACourses = 0;
			Course::setNumOfAvailCourses(_currNumofACourses);
			_yearOfStudy = 0;
		}
	private:
		int _yearOfStudy;
		std::string _name;
		std::int32_t _maxNumOfACourses;
		std::int32_t _currNumofACourses;
		std::map<std::string, Course> _listOfChCourses;
		friend std::ostream& operator<<(std::ostream& out, Study& s);
	};

	std::ostream& operator<<(std::ostream& out, Study& s)
	{
		out << s.getNameOfStudent() << ", year " << s.getYearOfStudy() << ", average grade: " << s.averageGrade() << ":\n";
		std::size_t i = 0;
		for(auto t: s._listOfChCourses)
		{
			std::cout << i + 1 << " " << t.second.getCourseName() << ", area: " << t.second.getScienceArea() << ", mark: " << t.second.getMark() << std::endl;
			i++;
		}
		return out;
	}
}
