#include "GroupService.h"

GroupService::GroupService()
{

}

/* 通过id查找群 */
Group *GroupService::findGroupById(const uint32_t &id)
{
	return gd.findOne(id);
}

