#include "configurator.h"

#include <iostream>
#include <stdlib.h>

namespace smartHome {
namespace configuration {

Configurator::Configurator(std::string _fName)
: m_fName(_fName)
{

}

void Configurator::parsing()
{
	std::ifstream file;
  file.open(m_fName.c_str());
	if(file.is_open()) {
		std::string line;

		while(file.good()) {
			DeviceParams* tmp = new DeviceParams;
			size_t tokenEnd;
			size_t lineLength;
			char curr[20];

			getline(file, line); // id
			if(line.empty()) {
				break;
			}
			tmp->m_id = line;
			std::cout << tmp->m_id << std::endl;

      getline(file, line); // type
			tokenEnd = line.find_first_of("=") + 1;
			lineLength = line.length();
			line.copy(curr, lineLength - tokenEnd + 1, tokenEnd);
			curr[lineLength - tokenEnd] = '\0';
			tmp->m_type = curr;
			std::cout << tmp->m_type << std::endl;

			getline(file, line); // room
			tokenEnd = line.find_first_of("=") + 1;
			lineLength = line.length();
			line.copy(curr, lineLength - tokenEnd + 1, tokenEnd);
			curr[lineLength - tokenEnd] = '\0';
			tmp->m_room = curr;
			std::cout << tmp->m_room << std::endl;

			getline(file, line); // floor
			tokenEnd = line.find_first_of("=") + 1;
			lineLength = line.length();
			line.copy(curr, lineLength - tokenEnd + 1, tokenEnd);
			curr[lineLength - tokenEnd] = '\0';
			tmp->m_floor = atoi(curr);
			std::cout << tmp->m_floor << std::endl;

			getline(file, line); // log
			tokenEnd = line.find_first_of("=") + 1;
			lineLength = line.length();
			line.copy(curr, lineLength - tokenEnd + 1, tokenEnd);
			curr[lineLength - tokenEnd] = '\0';
			tmp->m_log = curr;
			std::cout << tmp->m_log << std::endl;

			getline(file, line); // config
			tokenEnd = line.find_first_of("=") + 1;
			lineLength = line.length();
			line.copy(curr, lineLength - tokenEnd + 1, tokenEnd);
			curr[lineLength - tokenEnd] = '\0';
			tmp->m_config = curr;
			std::cout << tmp->m_config << std::endl;

			m_DPWQ.enqueue(tmp);

    }
    file.close();
  }


}


}} // smartHome::configuration
