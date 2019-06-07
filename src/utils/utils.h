/*  vim:set softtabstop=2 shiftwidth=2 tabstop=2 expandtab: */

#ifndef _UTILS_H
#define _UTILS_H

#include <chrono>
#include <string>

using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

/* Get current time since epoch in nanosec */
inline uint64_t get_time_nanosec()
{
  nanoseconds ts;
  ts = duration_cast<nanoseconds>(system_clock::now().time_since_epoch());

  return ts.count();
}

/* Conversion methods between xpaths and gNMI paths */
inline string gnmi_to_xpath(const Path& path)
{
  string str = "";

  if (path.elem_size() <= 0)
    return str;

  /* pipeline-gnmi collector puts YANG namespace in origin field */
  if (!path.origin().empty())
    str += path.origin() + ":";

  //iterate over the list of PathElem of a gNMI path
  for (auto &node : path.elem()) {
    str += "/";
    str += node.name();
    for (auto key : node.key()) //0 or 1 iteration
      str += "[" + key.first + "=\"" + key.second + "\"]";
  }

  return str;
}

#endif // _UTILS_H
