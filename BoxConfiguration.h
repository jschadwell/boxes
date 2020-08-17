#ifndef BOX_CONFIGURATION_H
#define BOX_CONFIGURATION_H

#include <vector>
#include <string>

using BoxConfigurationIterator = std::vector<std::string>::iterator;

class BoxConfiguration {
public:
    BoxConfiguration(std::string name);
    ~BoxConfiguration() = default;

    std::string& getName();
    bool addChild(std::string name);
    BoxConfigurationIterator begin();
    BoxConfigurationIterator end();

private:
	std::string _name;
	std::vector<std::string> _children;
};

using BoxConfigurationPtr = std::unique_ptr<BoxConfiguration>;

#endif // BOX_CONFIGURATION_H