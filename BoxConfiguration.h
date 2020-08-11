#ifndef BOX_CONFIGURATION_H
#define BOX_CONFIGURATION_H

#include <vector>
#include <string>

using ChildSet = std::vector<std::string>;

class BoxConfiguration {
public:
    BoxConfiguration(std::string id);
    ~BoxConfiguration() = default;

    std::string& getId();
    bool addChild(std::string id);
    const ChildSet& getChildren() const;
    void print();

private:
	std::string _id;
	ChildSet _children;
};

#endif // BOX_CONFIGURATION_H