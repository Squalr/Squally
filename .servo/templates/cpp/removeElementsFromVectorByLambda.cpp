this->myVector.erase(std::remove_if(this->myVector.begin(), this->myVector.end(), [=](const MyClass& myClass)
{
	return myClass.property == 0;
});
