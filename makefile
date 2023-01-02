DAY = $(1)

newDay:
	cp project/days/day.h project/days/day$(DAY).h
	sed -i.bak 's/dayX/day$(DAY)/' project/days/day$(DAY).h
	cp project/days/day.cpp project/days/day$(DAY).cpp
	sed -i.bak 's/dayX/day$(DAY)/g' project/days/day$(DAY).cpp
	rm project/days/*.bak
	touch project/inputs/day$(DAY)
	touch project/inputs/day$(DAY)Test

