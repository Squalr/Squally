std::sort(this->myVector.begin(), this->myVector.end(), [=](const MyClass & a, const MyClass & b) -> bool
{ 
    return a.property {{comparison}} b.property; 
});