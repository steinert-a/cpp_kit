#pragma once

// defines
#define UNDEF			(-1)

#define DELETE_POINTER(p) {if(p){delete (p);(p)=NULL;}}
#define DELETE_ARRAY(p) {if(p){delete[] (p);(p)=NULL;}}

#define RELEASE_POINTER(p) {if(p){(p)->Release();(p)=NULL;}}

#define FOR_EACH(it,stl) for(auto it = ((stl).begin()); it != ((stl).end()); it++)
#define FOR_EACH_REVERSE(it,stl) for(auto it = ((stl).rbegin()); it != ((stl).rend()); it++)