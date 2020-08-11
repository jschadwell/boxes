#ifndef BOX_CONFIGURATION_H
#define BOX_CONFIGURATION_H

#include <vector>
#include <string>

using BoxConfigurationIterator = std::vector<std::string>::iterator;

class BoxConfiguration {
public:
    BoxConfiguration(std::string id);
    ~BoxConfiguration() = default;

    std::string& getId();
    bool addChild(std::string id);
    BoxConfigurationIterator begin();
    BoxConfigurationIterator end();

private:
	std::string _id;
	std::vector<std::string> _children;
};

using BoxConfigurationPtr = std::unique_ptr<BoxConfiguration>;

#endif // BOX_CONFIGURATION_H