/*
 * PatternsDefault.cpp
 *
 *  Created on: May 18, 2012
 *      Author: jsepulve
 */

#include "PatternFactory.h"

//using namespace std;

namespace patterns {

    
PatternFactory* PatternFactory::m_Instance = NULL;
int PatternFactory::m_NumInstances = 0;

//const PatternFactory::Element PatternFactory::elements [MAX_ELEMENTS] = {
const PatternFactory::Element PatternFactory::elements [] = {
    {   //Pattern1: 4 pyramid mask: 11       
        2048,   {
                { PYRAMID_POINTS, {0,1,5,4,11}            },
                { PYRAMID_POINTS, {1,2,6,5,11}            },
                { PYRAMID_POINTS, {2,3,7,6,11}            },
                { PYRAMID_POINTS, {5,6,7,4,11}            } }
    },
    {   //Pattern2: 3 prisms //ARREGLADO mask: 11|19
        526336, {
                { PRISM_POINTS,   {0,1,11,4,5,19}         },
                { PRISM_POINTS,   {1,2,11,5,6,19}         },
                { PRISM_POINTS,   {2,3,11,6,7,19}         } }
    },   
    {   //Pattern3: 6 tetrahedra - 2 pyramid  mask: 11|17  
        133120, {
                { TETRA_POINTS,   {1,17,2,11}             },
                { TETRA_POINTS,   {4,11,7,17}             },
                { TETRA_POINTS,   {1,5,17,11}             },
                { TETRA_POINTS,   {5,4,17,11}             },
                { TETRA_POINTS,   {2,17,6,11}             },
                { TETRA_POINTS,   {17,7,6,11}             },
                { PYRAMID_POINTS, {0,4,5,1,11}            },
                { PYRAMID_POINTS, {2,6,7,3,11}            } }
    },
    {   //Pattern4: 6 tetrahedra - 2 pyramid  mask: 11|13
        10240,  {
                { TETRA_POINTS,   {0,13,1,11}             },
                { TETRA_POINTS,   {4,5,13,11}             },
                { TETRA_POINTS,   {0,4,13,11}             },
                { TETRA_POINTS,   {1,2,11,13}              },
                { TETRA_POINTS,   {5,6,13,11}             },
                { TETRA_POINTS,   {13,6,2,11}             },
                { PYRAMID_POINTS, {2,3,7,6,11}            },
                { PYRAMID_POINTS, {4,5,6,7,11}            } }

    },
    {//Pattern4.1 (Jorge): 6 tetrahedra - 2 pyramid    11|14 ARREGLADO
         18432, {
                { TETRA_POINTS,    {11,1,14,5  }          },
                { TETRA_POINTS,    {11,1,2,14  }          },
                { TETRA_POINTS,    {11,5,14,6  }          },
                { TETRA_POINTS,    {11,2,3,14  }          },
                { TETRA_POINTS,    {11,14,3,7  }          },
                { TETRA_POINTS,    {11,6,14,7  }          },
                { PYRAMID_POINTS,  {4,5,1,0,11 }          },
                { PYRAMID_POINTS,  {5,4,7,6,11 }          }  }
    },
    {//Pattern5: 12 tetrahedra mask:11|13|18
         272384,{
                { TETRA_POINTS,   {0,1,13,11}             },
                { TETRA_POINTS,   {4,13,5,11}             },
                { TETRA_POINTS,   {0,13,4,11}             },
                { TETRA_POINTS,   {3,18,7,11}             },
                { TETRA_POINTS,   {4,18,7,11}             },
                { TETRA_POINTS,   {4,5,18,11}             },
                { TETRA_POINTS,   {2,6,18,11}             },
                { TETRA_POINTS,   {2,3,18,11}             },
                { TETRA_POINTS,   {13,1,2,11}             },
                { TETRA_POINTS,   {5,13,6,11}             },
                { TETRA_POINTS,   {2,6,13,11}             },
                { TETRA_POINTS,   {5,6,18,11}             } }

    },
    {//Pattern6: 4 tetrahedra - 2 pyramid - 1 prism  mask: 11|13|19 ARREGLADO
         534528,{
                { TETRA_POINTS,   {0,1,13,11}             },
                { TETRA_POINTS,   {4,5,19,13}              },
                { TETRA_POINTS,   {1,2,13,11}             },
                { TETRA_POINTS,   {13,6,5,19}             },
                { PYRAMID_POINTS, {0,4,19,11,13}          },
                { PYRAMID_POINTS, {2,11,19,6,13}          },
                { PRISM_POINTS,   {2,3,11,6,7,19}         } }
    },
/*    
    {//Pattern6.1: 4 tetrahedra - 2 pyramid - 1 prism  mask :11|14|19 ARREGLADO
         542720,{
                { TETRA_POINTS,   {0,1,14,11}             },
                { TETRA_POINTS,   {4,5,9,14}              },
                { TETRA_POINTS,   {1,2,14,11}             },
                { TETRA_POINTS,   {14,6,5,19}             },
                { PYRAMID_POINTS, {0,4,19,11,14}          },
                { PYRAMID_POINTS, {2,11,19,6,14}          },
                { PRISM_POINTS,   {2,3,11,6,7,19}         } }
    },
*/    
    {//Pattern7: 5 tetrahedra - 3 pyramid   mask: 8|11|12
         6400,  {
                { TETRA_POINTS,   {0,8,11,12}             },
                { TETRA_POINTS,   {11,12,8,6}             },
                { TETRA_POINTS,   {2,11,8,6}              },
                { TETRA_POINTS,   {6,7,11,12}             },
                { TETRA_POINTS,   {5,12,8,6}              },
                { PYRAMID_POINTS, {1,2,6,5,8}             },
                { PYRAMID_POINTS, {2,3,7,6,11}            },
                { PYRAMID_POINTS, {4,5,6,7,12}            } }

    },
    {//Pattern8: 6 tetrahedra - 6 pyramid (Added centroid point) mask: 11|17|19
         657408,{
                { TETRA_POINTS,   {1,2,17,26}             },
                { TETRA_POINTS,   {2,6,17,26}             },
                { TETRA_POINTS,   {1,5,17,26}             },
                { TETRA_POINTS,   {0,1,11,26}             },
                { TETRA_POINTS,   {2,3,11,26}             },
                { TETRA_POINTS,   {1,2,11,26}             },
                { PYRAMID_POINTS, {3,7,19,11,26}          },
                { PYRAMID_POINTS, {0,4,19,11,26}          },
                { PYRAMID_POINTS, {0,1,5,4,26}            },
                { PYRAMID_POINTS, {2,3,7,6,26}            },
                { PYRAMID_POINTS, {4,5,17,19,26}          },
                { PYRAMID_POINTS, {17,6,7,19,26}          } }

    },
    {//Pattern9: 2 tetrahedra - 1 pyramid - 2 prism  mask: 11|12|19 ARREGLADO
         530432,{
                { TETRA_POINTS,   {1,12,0,11}             },
                { TETRA_POINTS,   {5,12,4,19}             },
                { PYRAMID_POINTS, {1,11,19,5,12}          },
                { PRISM_POINTS,   {2,3,11,6,7,19}         },
                { PRISM_POINTS,   {1,2,11,5,6,19}         } }

    },
/*
    {//Pattern9.1: 2 tetrahedra - 1 pyramid - 2 prism mask: 11|15|19 ERROR
         559104,{
                { TETRA_POINTS,   {2,3,11,15}             },
                { TETRA_POINTS,   {6,7,15,19}             },
                { PYRAMID_POINTS, {2,11,19,6,15}          },
                { PRISM_POINTS,   {0,1,11,4,5,19}         },
                { PRISM_POINTS,   {1,2,6,19,11}           } } <---falta un nodo
    },
*/    
    {//Pattern10: 2 tetrahedra - 3 pyramid - 1 prism  //mask: 8|11|19 ARREGLADO
         526592,{
                { TETRA_POINTS,   {4,5,19,8}              },
                { TETRA_POINTS,   {6,19,8,5}              },
                { PYRAMID_POINTS, {0,11,19,4,8}           },
                { PYRAMID_POINTS, {1,2,6,5,8}             },
                { PYRAMID_POINTS, {2,6,19,11,8}           },
                { PRISM_POINTS,   {2,3,11,6,7,19}         } }

    },
    {//Pattern10.1: 2 tetrahedra - 3 pyramid - 1 prism  //mask: 10|11|19 ARREGLADO
         527360,{
                { TETRA_POINTS,   {6,7,19,10}              },
                { TETRA_POINTS,   {5,6,10,19}              },
                { PYRAMID_POINTS, {3,11,19,7,10}           },
                { PYRAMID_POINTS, {1,2,6,5,10}             },
                { PYRAMID_POINTS, {1,5,19,11,10}           },
                { PRISM_POINTS,   {0,1,11,4,5,19}         } }

    },
    /*{//Pattern11: 2 tetrahedra - 4 pyramid - 1 prism //mask:11|12|15|19|24
         17340416,{
                { TETRA_POINTS,   {1,24,12,5}             },
                { TETRA_POINTS,   {6,24,15,2}             },
                { PYRAMID_POINTS, {0,11,24,12,1}          },
                { PYRAMID_POINTS, {11,3,15,24,2}          },
                { PYRAMID_POINTS, {15,7,19,24,6}          },
                { PYRAMID_POINTS, {12,24,19,4,5}          },
                { PRISM_POINTS,   {19,11,2,6,5,1}         } }

    },*/
	{//Pattern11 (Claudio): 4 tetrahedra - 5 pyramid //mask:11|12|15|19|24
		17340416,{
			{ TETRA_POINTS,   {1,24,12,5}             },
			{ TETRA_POINTS,   {6,24,15,2}             },
			{ TETRA_POINTS,   {6,19,24,5}             },
			{ TETRA_POINTS,   {2,24,11,1}             },
			{ PYRAMID_POINTS, {0,11,24,12,1}          },
			{ PYRAMID_POINTS, {11,3,15,24,2}          },
			{ PYRAMID_POINTS, {15,7,19,24,6}          },
			{ PYRAMID_POINTS, {12,24,19,4,5}          },
			{ PYRAMID_POINTS, {1,5,6,2,24}         } }
		
    },
    {//Pattern12: 2 hexahedra //mask:9|11|17|19
         657920,{
                { HEXA_POINTS,    {0,1,9,11,4,5,17,19}    },
                { HEXA_POINTS,    {11,9,2,3,19,17,6,7}    } }

    },
    {//Pattern13 (Jorge): 5 tetrahedra - 4 pyramid //mask:11|13|14|19 ARREGLADO
         550912,{
                { TETRA_POINTS,   {0,1,11,13}             },
                { TETRA_POINTS,   {4,13,19,5}             },
                { TETRA_POINTS,   {19,14,7,6}             },
                { TETRA_POINTS,   {11,2,3,14}             },
                { TETRA_POINTS,   {11,13,14,19}           },
                { PYRAMID_POINTS, {1,13,14,2,11}           },
                { PYRAMID_POINTS, {13,14,6,5,19}          },
                { PYRAMID_POINTS, {11,19,7,3,14}          },
                { PYRAMID_POINTS, {11,19,4,0,13}          } }

    },
    {//Pattern14: 4 prism  mask:8|10|12|15 ARREGLADO
         38144, {
                { PRISM_POINTS,   {6,10,15,5,8,12}        },
                { PRISM_POINTS,   {1,5,8,2,6,10}          },
                { PRISM_POINTS,   {6,7,15,5,4,12}         },
                { PRISM_POINTS,   {10,3,15,8,0,12}        } }

    },
    {//Pattern15 (Jorge): 3 tetrahedra - 3 pyramid - 1 prism //11|12|13|19 MODIFICADO
         538624,{
                { TETRA_POINTS,   {11,1,2,13}             },
                { TETRA_POINTS,   {11,12,13,19}             },
                { TETRA_POINTS,   {19,13,6,5}           },
                { PYRAMID_POINTS, {12,13,1,0,11}          },
                { PYRAMID_POINTS, {4,5,13,12,19}          },
                { PYRAMID_POINTS, {11,2,6,19,13}          },
                { PRISM_POINTS,   {3,11,2,7,19,6}         } }

    },
    {//Pattern16 (Jorge):2 tetrahedra - 4 pyramis - 2 prism //9|11|12|15|19|24 ARREGLADO
        17340928,{
                { TETRA_POINTS,   {24,5,6,19}             },
                { TETRA_POINTS,   {24,5,9,6}              },
                { PYRAMID_POINTS, {19,24,15,7,6}          },
                { PYRAMID_POINTS, {4,12,24,19,5}          },
                { PYRAMID_POINTS, {12,1,9,24,5}           },
                { PYRAMID_POINTS, {24,9,2,15,6}           },
                { PRISM_POINTS,   {0,12,1,11,24,9}        },
                { PRISM_POINTS,   {11,24,9,3,15,2}        } }

    },
    {//Pattern17: 6 tetrahedra - 5 pyramid // 8|11|12|15|19|24
          17340672,{
                { TETRA_POINTS,   {5,19,6,24}             },
                { TETRA_POINTS,   {2,15,6,24}             },
                { TETRA_POINTS,   {8,24,5,12}             },
                { TETRA_POINTS,   {8,1,5,24}              },
                { TETRA_POINTS,   {2,11,8,24}             },
                { TETRA_POINTS,   {8,2,1,24}              },
                { PYRAMID_POINTS, {15,7,19,24,6}          },
                { PYRAMID_POINTS, {4,19,24,12,5}          },
                { PYRAMID_POINTS, {15,24,11,3,2}          },
                { PYRAMID_POINTS, {12,24,11,0,8}          },
                { PYRAMID_POINTS, {1,5,6,2,24}            } }

    },
    {    //Pattern18 (Jorge): 4 tetrahedra - 5 pyramid - 1 prism (Added mid point) mask: 8|10|12|15|18 MODIFICADO
         300288,{
                { TETRA_POINTS,   {1,5,26,8}              },
                { TETRA_POINTS,   {26,5,6,18}             },
                { TETRA_POINTS,   {26,10,15,18}           },
                { TETRA_POINTS,   {12,8,26,5}             },
                { TETRA_POINTS,   {12,5,26,4}             },
                { TETRA_POINTS,   {4,5,26,18}             },
                { TETRA_POINTS,   {4,26,7,18}             },
                { TETRA_POINTS,   {7,26,15,18}            },
                { PYRAMID_POINTS, {10,2,6,18,26}          },
                { PYRAMID_POINTS, {8,1,2,10,26}           },
                { PYRAMID_POINTS, {1,5,6,2,26}            },
                { PYRAMID_POINTS, {4,12,15,7,26}          },
                { PYRAMID_POINTS, {12,8,10,15,26}         },
                { PRISM_POINTS,   {0,12,8,3,15,10}        } }
    },
    {//Pattern19(Jorge): 10 tetrahedra - 8 pyramid mask: 9|11|12|14|15|19|24 MODIFICADO
         17357312,{
                { TETRA_POINTS,   {2,9,14,26}            },
                { TETRA_POINTS,   {7,26,6,19}            },
                { TETRA_POINTS,   {26,9,14,5}            },
                { TETRA_POINTS,   {5,6,19,26}            },
                { TETRA_POINTS,   {6,14,5,26}            },
                { TETRA_POINTS,   {1,5,9,26 }            },
                { TETRA_POINTS,   {4,26,19,5}            },
                { TETRA_POINTS,   {0,1,26,12}            },
                { TETRA_POINTS,   {4,12,26,5}            },
                { TETRA_POINTS,   {12,1,26,5}            },
                { PYRAMID_POINTS, {3,2,14,15,26}         },
                { PYRAMID_POINTS, {11,9,2,3,26}          },
                { PYRAMID_POINTS, {24,11,3,15,26}        },
                { PYRAMID_POINTS, {19,24,15,7,26}        },
                { PYRAMID_POINTS, {15,14,6,7,26}         },
                { PYRAMID_POINTS, {0,1,9,11,26}          },
                { PYRAMID_POINTS, {4,12,24,19,26}        },
                { PYRAMID_POINTS, {12,0,11,24,26}       }}
    },




    {//Pattern20: 6 prism mask: 11|12|13|14|15|19|24 ARREGLADO
         17364992,{
                { PRISM_POINTS,   {0,1,11,12,13,24}       },
                { PRISM_POINTS,   {2,3,11,14,15,24}       },
                { PRISM_POINTS,   {14,15,24,6,7,19}       },
                { PRISM_POINTS,   {4,5,19,12,13,24}       },
                { PRISM_POINTS,   {1,2,11,13,14,24}       },
                { PRISM_POINTS,   {5,6,19,13,14,24}       } }

    },
    {//Pattern21: 4 hexahedra mask: 9|11|12|13|17|19|22|24 (key arreglada)
         21690880,  {
                { HEXA_POINTS,    {0,1,9,11,12,13,22,24}  },
                { HEXA_POINTS,    {12,13,22,24,4,5,17,19} },
                { HEXA_POINTS,    {11,9,2,3,24,22,14,15}  },
                { HEXA_POINTS,    {24,22,14,15,19,17,6,7} } }

    },
    {//Pattern22: 4 tetrahedra - 3 pyramid mask: 11|12
        6144, {
                { TETRA_POINTS,   {1,11,0,12}             },
                { TETRA_POINTS,   {1,12,5,11}             },
                { TETRA_POINTS,   {11,12,7,6}             },
                { TETRA_POINTS,   {11,12,5,6}             },
                { PYRAMID_POINTS, {4,5,6,7,12}            },
                { PYRAMID_POINTS, {2,3,7,6,11}            },
                { PYRAMID_POINTS, {1,2,6,5,11}            } }

    },
    {//Pattern23 (Jorge): 3 tetrahedra - 6 pyramid - 2 prism MODIFICADO mask: 8|9|10|11|12|15|19|20|24
         18390784, {
                { TETRA_POINTS,   {5,20,6,9        }      },
                { TETRA_POINTS,   {5,24,6,19       }      }, 
                { TETRA_POINTS,   {5,24,6,20       }      }, 
                { PYRAMID_POINTS, {12,24,19,4,5    }      },  
                { PYRAMID_POINTS, {24,15,7,19,6    }      },  
                { PYRAMID_POINTS, {1,8,20,9,5      }      },  
                { PYRAMID_POINTS, {9,2,10,20,6     }      },  
                { PYRAMID_POINTS, {12,8,20,24,5    }      },  
                { PYRAMID_POINTS, {24,20,10,15,6   }      }, 
                { PRISM_POINTS,   {0,8,12,11,20,24 }      }, 
                { PRISM_POINTS,   {15,3,10,24,11,20}      }} 
    },
    {//Pattern24 (Jorge): 12 tetrahedra - 12 pyramid (Added centroid point) MODIFICADO mask: 8|9|10|11|12|13|15|16|19|20|21|24
         20561664, {
                { TETRA_POINTS,   {16,19,6,26   }         }, 
                { TETRA_POINTS,   {4,26,19,16   }         }, 
                { TETRA_POINTS,   {1,13,9,26    }         }, 
                { TETRA_POINTS,   {5,16,6,26    }         }, 
                { TETRA_POINTS,   {13,9,6,26    }         }, 
                { TETRA_POINTS,   {13,5,6,26    }         }, 
                { TETRA_POINTS,   {7,19,26,6    }         }, 
                { TETRA_POINTS,   {3,10,15,26   }         }, 
                { TETRA_POINTS,   {10,6,15,26   }         }, 
                { TETRA_POINTS,   {15,6,7,26    }         }, 
                { TETRA_POINTS,   {10,26,2,6    }         }, 
                { TETRA_POINTS,   {9,6,2,26     }         }, 
                { PYRAMID_POINTS, {0,8,20,11,26 }         }, 
                { PYRAMID_POINTS, {12,21,8,0,26 }         }, 
                { PYRAMID_POINTS, {12,0,11,24,26}         }, 
                { PYRAMID_POINTS, {4,12,24,19,26}         },  
                { PYRAMID_POINTS, {4,16,21,12,26}         },  
                { PYRAMID_POINTS, {8,1,9,20,26  }         },  
                { PYRAMID_POINTS, {13,1,8,21,26 }         },  
                { PYRAMID_POINTS, {5,13,21,16,26}         },  
                { PYRAMID_POINTS, {11,20,10,3,26}         },  
                { PYRAMID_POINTS, {24,11,3,15,26}         },  
                { PYRAMID_POINTS, {19,24,15,7,26}         },  
                { PYRAMID_POINTS, {20,9,2,10,26 }         }  } 
    },
    {//Pattern25 (Jorge): 2 hexa - 5 prism NUEVO mask: 8|10|11|12|13|14|15|16|18|19|21|23|24
         28179712, {
         { PRISM_POINTS,   {3,10,11,15,23,24      }             },
         { PRISM_POINTS,   {15,23,24,7,18,19      }             },
         { PRISM_POINTS,   {0,8,11,12,21,24       }             },
         { PRISM_POINTS,   {12,21,24,4,16,19      }             },
         { PRISM_POINTS,   {11,8,10,24,21,23      }             },
         { PRISM_POINTS,   {24,21,23,19,16,18     }             },
         { HEXA_POINTS,    {21,13,14,23,16,5,6,18 }             },
         { HEXA_POINTS,    {8,1,2,10,21,13,14,23  }             }}
	},
	{63962624, {
			{TETRA_POINTS, {12,13,16,26}},
			{TETRA_POINTS, {16,5,13,26}},
			{TETRA_POINTS, {4,16,12,26}},
			{TETRA_POINTS, {11,9,10,26}},
			{TETRA_POINTS, {10,2,9,26}},
			{TETRA_POINTS, {3,10,11,26}},
			{PYRAMID_POINTS, {0,1,13,12,26}},
			{PYRAMID_POINTS, {0,1,9,11,26}},
			{PYRAMID_POINTS, {1,9,22,13,26}},
			{PYRAMID_POINTS, {13,22,17,5,26}},
			{PYRAMID_POINTS, {5,17,25,16,26}},
			{PYRAMID_POINTS, {4,16,25,19,26}},
			{PYRAMID_POINTS, {4,12,24,19,26}},
			{PYRAMID_POINTS, {0,11,24,12,26}},
			{PYRAMID_POINTS, {9,2,14,22,26}},
			{PYRAMID_POINTS, {10,2,14,23,26}},
			{PYRAMID_POINTS, {22,14,6,17,26}},
			{PYRAMID_POINTS, {14,23,18,6,26}},
			{PYRAMID_POINTS, {25,17,6,18,26}},
			{PYRAMID_POINTS, {10,3,15,23,26}},
			{PYRAMID_POINTS, {3,11,24,15,26}},
			{PYRAMID_POINTS, {23,15,7,18,26}},
			{PYRAMID_POINTS, {24,19,7,15,26}},
			{PYRAMID_POINTS, {25,18,7,19,26}}
		}},
	{33554176, {
			{PYRAMID_POINTS, {21,13,1,8,26}},
			{PYRAMID_POINTS, {21,16,5,13,26}},
			{PYRAMID_POINTS, {0,8,21,12,26}},
			{PYRAMID_POINTS, {4,16,21,12,26}},
			{PYRAMID_POINTS, {0,8,20,11,26}},
			{PYRAMID_POINTS, {8,1,9,20,26}},
			{PYRAMID_POINTS, {20,9,2,10,26}},
			{PYRAMID_POINTS, {11,20,10,3,26}},
			{PYRAMID_POINTS, {4,19,24,12,26}},
			{PYRAMID_POINTS, {19,7,15,24,26}},
			{PYRAMID_POINTS, {3,11,24,15,26}},
			{PYRAMID_POINTS, {0,11,24,12,26}},
			{PYRAMID_POINTS, {2,10,23,14,26}},
			{PYRAMID_POINTS, {14,23,18,6,26}},
			{PYRAMID_POINTS, {10,3,15,23,26}},
			{PYRAMID_POINTS, {23,15,7,18,26}},
			{PYRAMID_POINTS, {1,9,22,13,26}},
			{PYRAMID_POINTS, {9,2,14,22,26}},
			{PYRAMID_POINTS, {13,22,17,5,26}},
			{PYRAMID_POINTS, {22,14,6,17,26}},
			{PYRAMID_POINTS, {16,17,18,19,26}},
			{TETRA_POINTS, {4,16,19,26}},
			{TETRA_POINTS, {5,16,17,26}},
			{TETRA_POINTS, {6,17,18,26}},
			{TETRA_POINTS, {7,18,19,26}}
		}},
	{3358464, {
			{PRISM_POINTS, {0,11,12,8,20,21}},
			{PRISM_POINTS, {8,20,21,1,9,13}},
			{PYRAMID_POINTS, {4,12,21,16,7}},
			{PYRAMID_POINTS, {20,21,12,11,7}},
			{PYRAMID_POINTS, {20,11,3,10,7}},
			{PYRAMID_POINTS, {5,13,21,16,17}},
			{PYRAMID_POINTS, {9,13,21,20,17}},
			{PRISM_POINTS, {9,17,20,2,6,10}},
			{TETRA_POINTS, {7,17,16,21}},
			{TETRA_POINTS, {7,17,21,20}},
			{PYRAMID_POINTS, {6,17,20,10,7}}
		}},
	{3751680, {
			{PRISM_POINTS, {1,9,13,8,20,21}},
			{PRISM_POINTS, {8,20,21,0,11,12}},
			{PYRAMID_POINTS, {5,13,21,16,6}},
			{PYRAMID_POINTS, {20,21,13,9,6}},
			{PYRAMID_POINTS, {20,9,2,10,6}},
			{PYRAMID_POINTS, {4,12,21,16,19}},
			{PYRAMID_POINTS, {11,12,21,20,19}},
			{PRISM_POINTS, {11,19,20,3,7,10}},
			{TETRA_POINTS, {6,19,16,21}},
			{TETRA_POINTS, {6,19,21,20}},
			{PYRAMID_POINTS, {7,19,20,10,6}}
		}},
	{67108608, {
			{HEXA_POINTS, {0,8,20,11,12,21,26,24}},
			{HEXA_POINTS, {8,1,9,20,21,13,22,26}},
			{HEXA_POINTS, {12,21,26,24,4,16,25,19}},
			{HEXA_POINTS, {21,13,22,26,16,5,17,25}},
			{HEXA_POINTS, {11,20,10,3,24,26,23,15}},
			{HEXA_POINTS, {24,26,23,15,19,25,18,7}},
			{HEXA_POINTS, {20,9,2,10,26,22,14,23}},
			{HEXA_POINTS, {26,22,14,23,25,17,6,18}}
		}},
	{20578048, {
			{PYRAMID_POINTS, {1,8,21,13,26}},
			{PYRAMID_POINTS, {1,8,20,9,26}},
			{TETRA_POINTS, {1,9,13,26}},
			{PYRAMID_POINTS, {2,10,20,9,14}},
			{TETRA_POINTS, {26,14,9,20}},
			{TETRA_POINTS, {9,13,14,26}},
			{TETRA_POINTS, {26,20,10,14}},
			{PYRAMID_POINTS, {3,11,20,10,26}},
			{PYRAMID_POINTS, {3,11,24,15,26}},
			{TETRA_POINTS, {15,3,10,26}},
			{TETRA_POINTS, {10,14,15,26}},
			{PYRAMID_POINTS, {0,8,21,12,26}},
			{PYRAMID_POINTS, {0,8,20,11,26}},
			{PYRAMID_POINTS, {0,11,24,12,26}},
			{PYRAMID_POINTS, {6,7,15,14,26}},
			{PYRAMID_POINTS, {7,19,24,15,26}},
			{TETRA_POINTS, {6,7,19,26}},
			{PYRAMID_POINTS, {4,12,24,19,26}},
			{TETRA_POINTS, {4,16,19,26}},
			{PYRAMID_POINTS, {4,12,21,16,26}},
			{TETRA_POINTS, {16,19,6,26}},
			{PYRAMID_POINTS, {5,13,21,16,26}},
			{TETRA_POINTS, {5,6,16,26}},
			{PYRAMID_POINTS, {5,6,14,13,26}}
		}},
	{1064704, {
			{PYRAMID_POINTS, {1,8,20,9,13}},
			{PYRAMID_POINTS, {0,8,20,11,12}},
			{PYRAMID_POINTS, {2,9,20,10,6}},
			{PYRAMID_POINTS, {11,20,10,3,7}},
			{PYRAMID_POINTS, {7,6,13,12,20}},
			{TETRA_POINTS, {12,13,20,8}},
			{TETRA_POINTS, {7,6,20,10}},
			{TETRA_POINTS, {13,20,6,9}},
			{TETRA_POINTS, {12,20,7,11}},
			{PRISM_POINTS, {13,5,6,12,4,7}}
		}},
	{2192128, {
			{PYRAMID_POINTS, {0,8,21,12,3}},
			{PYRAMID_POINTS, {1,8,21,13,9}},
			{TETRA_POINTS, {9,8,3,21}},
			{TETRA_POINTS, {9,21,14,3}},
			{TETRA_POINTS, {9,21,14,13}},
			{TETRA_POINTS, {3,12,7,21}},
			{TETRA_POINTS, {3,21,14,7}},
			{PYRAMID_POINTS, {4,12,21,16,7}},
			{PYRAMID_POINTS, {21,16,6,14,7}},
			{PRISM_POINTS, {14,13,21,6,5,16}},
			{TETRA_POINTS, {2,9,14,3}}
		}},
	{2210048, {
			{PYRAMID_POINTS, {1,8,21,13,2}},
			{PYRAMID_POINTS, {0,8,21,12,11}},
			{TETRA_POINTS, {11,8,2,21}},
			{TETRA_POINTS, {11,21,15,2}},
			{TETRA_POINTS, {11,21,15,12}},
			{TETRA_POINTS, {2,13,6,21}},
			{TETRA_POINTS, {2,21,15,6}},
			{PYRAMID_POINTS, {5,13,21,16,6}},
			{PYRAMID_POINTS, {21,16,7,15,6}},
			{PRISM_POINTS, {15,12,21,7,4,16}},
			{TETRA_POINTS, {3,11,15,2}}
		}},
	{9984, {
			{TETRA_POINTS, {10,13,9,6}},
			{TETRA_POINTS, {10,8,9,13}},
			{TETRA_POINTS, {1,8,9,13}},
			{TETRA_POINTS, {2,9,10,6}},
			{PRISM_POINTS, {4,0,8,7,3,10}},
			{PYRAMID_POINTS, {4,7,10,8,13}},
			{TETRA_POINTS, {7,10,6,13}},
			{PYRAMID_POINTS, {4,5,6,7,13}}
		}},
	{7424, {
			{TETRA_POINTS, {10,12,11,7}},
			{TETRA_POINTS, {10,8,11,12}},
			{TETRA_POINTS, {0,8,11,12}},
			{TETRA_POINTS, {3,11,10,7}},
			{PRISM_POINTS, {5,1,8,6,2,10}},
			{PYRAMID_POINTS, {5,6,10,8,12}},
			{TETRA_POINTS, {6,10,7,12}},
			{PYRAMID_POINTS, {5,4,7,6,12}}
		}},
	{71680, {
			{TETRA_POINTS, {0,1,11,12}},
			{PYRAMID_POINTS, {2,3,7,6,11}},
			{TETRA_POINTS, {4,12,16,7}},
			{TETRA_POINTS, {7,11,12,16}},
			{TETRA_POINTS, {11,12,1,16}},
			{TETRA_POINTS, {1,11,16,5}},
			{TETRA_POINTS, {6,7,16,11}},
			{TETRA_POINTS, {5,6,11,16}},
			{PYRAMID_POINTS, {1,2,6,5,11}}
		}},
	{74240, {
			{TETRA_POINTS, {1,0,9,13}},
			{PYRAMID_POINTS, {3,2,6,7,9}},
			{TETRA_POINTS, {5,13,16,6}},
			{TETRA_POINTS, {6,9,13,16}},
			{TETRA_POINTS, {9,13,0,16}},
			{TETRA_POINTS, {0,9,16,4}},
			{TETRA_POINTS, {7,6,16,9}},
			{TETRA_POINTS, {4,7,9,16}},
			{PYRAMID_POINTS, {0,3,7,4,9}}
		}},
	{6520576, {
			{PRISM_POINTS, {1,8,9,13,21,22}},
			{PRISM_POINTS, {9,10,22,8,11,21}},
			{TETRA_POINTS, {3,10,11,7}},
			{PYRAMID_POINTS, {0,8,21,12,11}},
			{PYRAMID_POINTS, {2,9,22,14,10}},
			{PYRAMID_POINTS, {10,11,21,22,7}},
			{TETRA_POINTS, {11,12,21,7}},
			{TETRA_POINTS, {10,14,22,7}},
			{PYRAMID_POINTS, {4,12,21,16,7}},
			{PYRAMID_POINTS, {16,17,22,21,7}},
			{PYRAMID_POINTS, {6,14,22,17,7}},
			{PRISM_POINTS, {13,21,22,5,16,17}}
		}},
	{55573248, {
			{PYRAMID_POINTS, {0,11,24,12,8}},
			{PYRAMID_POINTS, {3,15,24,11,26}},
			{PRISM_POINTS, {4,12,16,19,24,25}},
			{PRISM_POINTS, {19,24,25,7,15,18}},
			{TETRA_POINTS, {11,24,26,8}},
			{PYRAMID_POINTS, {2,3,11,9,26}},
			{TETRA_POINTS, {8,9,11,26}},
			{PYRAMID_POINTS, {2,3,15,14,26}},
			{PYRAMID_POINTS, {2,14,22,9,26}},
			{TETRA_POINTS, {13,22,26,8}},
			{TETRA_POINTS, {9,22,26,8}},
			{TETRA_POINTS, {12,24,26,8}},
			{PYRAMID_POINTS, {1,9,22,13,8}},
			{PYRAMID_POINTS, {12,24,25,16,26}},
			{PYRAMID_POINTS, {15,18,25,24,26}},
			{TETRA_POINTS, {14,15,18,26}},
			{PYRAMID_POINTS, {14,18,25,22,26}},
			{PYRAMID_POINTS, {13,16,25,22,26}},
			{PYRAMID_POINTS, {8,12,16,13,26}},
			{PRISM_POINTS, {5,13,16,17,22,25}},
			{PRISM_POINTS, {17,22,25,6,14,18}}
		}},
	{4420352, {
			{TETRA_POINTS, {0,8,12,3}},
			{TETRA_POINTS, {4,12,16,7}},
			{PYRAMID_POINTS, {2,14,22,9,3}},
			{TETRA_POINTS, {3,7,14,22}},
			{TETRA_POINTS, {8,9,3,22}},
			{PYRAMID_POINTS, {6,17,22,14,7}},
			{TETRA_POINTS, {8,12,22,3}},
			{TETRA_POINTS, {3,7,12,22}},
			{PYRAMID_POINTS, {1,9,22,13,8}},
			{TETRA_POINTS, {12,16,22,7}},
			{TETRA_POINTS, {7,16,17,22}},
			{PYRAMID_POINTS, {5,13,22,17,16}},
			{PYRAMID_POINTS, {8,12,16,13,22}}
		}},
	{31457024, {
			{TETRA_POINTS, {1,8,13,26}},
			{PYRAMID_POINTS, {1,8,20,9,26}},
			{PYRAMID_POINTS, {1,9,22,13,26}},
			{PYRAMID_POINTS, {2,9,22,14,26}},
			{PYRAMID_POINTS, {2,9,20,10,26}},
			{PYRAMID_POINTS, {2,14,23,10,26}},
			{PYRAMID_POINTS, {3,10,23,15,26}},
			{PYRAMID_POINTS, {3,11,20,10,26}},
			{PYRAMID_POINTS, {3,11,24,15,26}},
			{PYRAMID_POINTS, {0,11,24,12,26}},
			{PYRAMID_POINTS, {0,8,20,11,26}},
			{TETRA_POINTS, {0,8,12,26}},
			{PYRAMID_POINTS, {4,19,24,12,16}},
			{TETRA_POINTS, {16,12,26,24}},
			{TETRA_POINTS, {16,19,26,24}},
			{PYRAMID_POINTS, {7,18,23,15,26}},
			{PYRAMID_POINTS, {7,19,24,15,26}},
			{TETRA_POINTS, {7,18,19,26}},
			{PYRAMID_POINTS, {6,18,23,14,26}},
			{PYRAMID_POINTS, {6,14,22,17,26}},
			{TETRA_POINTS, {6,17,18,26}},
			{TETRA_POINTS, {26,22,17,16}},
			{TETRA_POINTS, {13,22,26,16}},
			{PYRAMID_POINTS, {5,17,22,13,16}},
			{PYRAMID_POINTS, {8,13,16,12,26}},
			{PYRAMID_POINTS, {16,17,18,19,26}}
		}},
	{56622848, {
			{PRISM_POINTS, {4,12,16,19,24,25}},
			{PRISM_POINTS, {19,24,25,7,15,18}},
			{PRISM_POINTS, {13,5,16,22,17,25}},
			{PRISM_POINTS, {22,17,25,14,6,18}},
			{PRISM_POINTS, {8,0,12,20,11,24}},
			{PRISM_POINTS, {20,11,24,10,3,15}},
			{PRISM_POINTS, {1,8,13,9,20,22}},
			{PRISM_POINTS, {9,20,22,2,10,14}},
			{HEXA_POINTS, {8,12,16,13,20,24,25,22}},
			{HEXA_POINTS, {20,24,25,22,10,15,18,14}}
		}},
	{17602816, {
			{PYRAMID_POINTS, {4,19,24,12,5}},
			{PYRAMID_POINTS, {7,19,24,15,18}},
			{PYRAMID_POINTS, {0,12,24,11,8}},
			{PYRAMID_POINTS, {3,11,24,15,2}},
			{TETRA_POINTS, {2,8,11,24}},
			{TETRA_POINTS, {5,18,19,24}},
			{TETRA_POINTS, {5,8,12,24}},
			{TETRA_POINTS, {2,15,18,24}},
			{TETRA_POINTS, {1,5,8,24}},
			{TETRA_POINTS, {5,6,18,24}},
			{TETRA_POINTS, {1,8,2,24}},
			{TETRA_POINTS, {2,6,18,24}},
			{PYRAMID_POINTS, {1,2,6,5,24}}
		}},
	{17358336, {
			{TETRA_POINTS, {2,9,14,10}},
			{PYRAMID_POINTS, {3,11,24,15,10}},
			{TETRA_POINTS, {9,10,11,24}},
			{TETRA_POINTS, {14,15,24,10}},
			{TETRA_POINTS, {9,14,24,10}},
			{PRISM_POINTS, {6,7,19,14,15,24}},
			{PYRAMID_POINTS, {4,12,24,19,5}},
			{PRISM_POINTS, {0,1,12,11,9,24}},
			{TETRA_POINTS, {9,14,24,5}},
			{PYRAMID_POINTS, {1,9,24,12,5}},
			{PYRAMID_POINTS, {6,14,24,19,5}}
		}},
	{21691136, {
			{PYRAMID_POINTS, {0,12,24,11,8}},
			{PYRAMID_POINTS, {9,11,24,22,8}},
			{PYRAMID_POINTS, {1,9,22,13,8}},
			{PYRAMID_POINTS, {12,13,22,24,8}},
			{HEXA_POINTS, {12,13,22,24,4,5,17,19}},
			{HEXA_POINTS, {2,3,11,9,14,15,24,22}},
			{HEXA_POINTS, {14,15,24,22,6,7,19,17}}
		}},
	{26016768, {
			{PRISM_POINTS, {4,5,19,12,13,24}},
			{PRISM_POINTS, {12,13,24,0,1,11}},
			{PRISM_POINTS, {7,18,19,15,23,24}},
			{PRISM_POINTS, {15,23,24,3,10,11}},
			{PRISM_POINTS, {5,18,19,13,23,24}},
			{PRISM_POINTS, {13,23,24,1,10,11}},
			{PRISM_POINTS, {5,6,18,13,14,23}},
			{PRISM_POINTS, {13,14,23,1,2,10}}
		}},
	{14155520, {
			{PYRAMID_POINTS, {0,8,20,11,12}},
			{PYRAMID_POINTS, {7,18,23,15,26}},
			{TETRA_POINTS, {11,3,15,26}},
			{PYRAMID_POINTS, {3,10,20,11,26}},
			{PYRAMID_POINTS, {3,10,23,15,26}},
			{TETRA_POINTS, {11,12,15,26}},
			{PYRAMID_POINTS, {4,7,15,12,26}},
			{TETRA_POINTS, {11,20,26,12}},
			{TETRA_POINTS, {8,20,26,12}},
			{PYRAMID_POINTS, {2,9,22,14,26}},
			{PYRAMID_POINTS, {2,9,20,10,26}},
			{PYRAMID_POINTS, {2,14,23,10,26}},
			{PYRAMID_POINTS, {6,14,23,18,26}},
			{PYRAMID_POINTS, {6,14,22,17,26}},
			{TETRA_POINTS, {6,17,18,26}},
			{PYRAMID_POINTS, {7,18,16,4,26}},
			{TETRA_POINTS, {16,17,18,26}},
			{PYRAMID_POINTS, {1,9,20,8,26}},
			{PYRAMID_POINTS, {1,9,22,13,26}},
			{TETRA_POINTS, {1,8,13,26}},
			{PYRAMID_POINTS, {5,13,22,17,16}},
			{PYRAMID_POINTS, {8,12,16,13,26}},
			{TETRA_POINTS, {4,12,16,26}},
			{TETRA_POINTS, {13,22,26,16}},
			{TETRA_POINTS, {17,22,26,16}}
		}},
	{623616, {
			{TETRA_POINTS, {4,16,19,0}},
			{TETRA_POINTS, {7,15,19,6}},
			{TETRA_POINTS, {3,10,15,0}},
			{TETRA_POINTS, {0,15,19,16}},
			{TETRA_POINTS, {6,16,19,15}},
			{TETRA_POINTS, {0,10,15,16}},
			{TETRA_POINTS, {6,10,15,16}},
			{TETRA_POINTS, {0,1,16,10}},
			{TETRA_POINTS, {1,5,16,10}},
			{TETRA_POINTS, {5,6,16,10}},
			{PYRAMID_POINTS, {1,2,6,5,10}}
		}},
	{80128, {
			{TETRA_POINTS, {0,8,11,12}},
			{TETRA_POINTS, {4,12,16,7}},
			{TETRA_POINTS, {7,11,12,16}},
			{TETRA_POINTS, {3,7,11,16}},
			{PYRAMID_POINTS, {2,3,7,6,16}},
			{TETRA_POINTS, {2,3,11,16}},
			{TETRA_POINTS, {2,8,11,13}},
			{TETRA_POINTS, {11,13,16,2}},
			{PYRAMID_POINTS, {8,12,16,13,11}},
			{TETRA_POINTS, {1,8,13,2}},
			{TETRA_POINTS, {2,6,13,16}},
			{TETRA_POINTS, {5,13,16,6}}
		}},
	{10407680, {
			{PRISM_POINTS, {3,11,15,10,20,23}},
			{PRISM_POINTS, {10,20,23,2,9,14}},
			{PYRAMID_POINTS, {7,15,23,18,19}},
			{PYRAMID_POINTS, {6,14,23,18,17}},
			{TETRA_POINTS, {17,18,19,23}},
			{PYRAMID_POINTS, {11,15,23,20,19}},
			{PYRAMID_POINTS, {9,14,23,20,17}},
			{TETRA_POINTS, {17,20,19,23}},
			{PRISM_POINTS, {0,4,8,11,19,20}},
			{PRISM_POINTS, {4,5,8,19,17,20}},
			{PRISM_POINTS, {1,5,8,9,17,20}}
		}},
	{983040, {
			{TETRA_POINTS, {5,16,17,1}},
			{TETRA_POINTS, {4,16,19,0}},
			{TETRA_POINTS, {7,18,19,3}},
			{TETRA_POINTS, {6,17,18,2}},
			{TETRA_POINTS, {0,3,19,16}},
			{PYRAMID_POINTS, {16,17,18,19,3}},
			{TETRA_POINTS, {2,3,18,17}},
			{TETRA_POINTS, {0,3,16,17}},
			{PYRAMID_POINTS, {0,1,2,3,17}},
			{TETRA_POINTS, {0,1,16,17}}
		}},
	{26147840, {
			{PYRAMID_POINTS, {1,2,14,13,26}},
			{TETRA_POINTS, {1,2,10,26}},
			{PYRAMID_POINTS, {2,14,23,10,26}},
			{TETRA_POINTS, {1,11,10,26}},
			{PYRAMID_POINTS, {6,18,23,14,26}},
			{PYRAMID_POINTS, {11,10,23,24,26}},
			{PYRAMID_POINTS, {19,18,23,24,26}},
			{TETRA_POINTS, {6,14,17,26}},
			{TETRA_POINTS, {6,18,17,26}},
			{TETRA_POINTS, {13,14,17,26}},
			{TETRA_POINTS, {5,13,17,26}},
			{TETRA_POINTS, {19,18,17,26}},
			{TETRA_POINTS, {1,0,11,26}},
			{PYRAMID_POINTS, {1,0,12,13,26}},
			{PYRAMID_POINTS, {13,12,4,5,26}},
			{PYRAMID_POINTS, {5,4,19,17,26}},
			{PYRAMID_POINTS, {4,19,24,12,26}},
			{PYRAMID_POINTS, {0,11,24,12,26}},
			{PRISM_POINTS, {7,19,18,15,24,23}},
			{PRISM_POINTS, {15,24,23,3,11,10}}
		}},
	{13563392, {
			{PYRAMID_POINTS, {0,3,15,12,26}},
			{TETRA_POINTS, {0,3,10,26}},
			{PYRAMID_POINTS, {3,15,23,10,26}},
			{TETRA_POINTS, {0,9,10,26}},
			{PYRAMID_POINTS, {7,18,23,15,26}},
			{PYRAMID_POINTS, {9,10,23,22,26}},
			{PYRAMID_POINTS, {17,18,23,22,26}},
			{TETRA_POINTS, {7,15,19,26}},
			{TETRA_POINTS, {7,18,19,26}},
			{TETRA_POINTS, {12,15,19,26}},
			{TETRA_POINTS, {4,12,19,26}},
			{TETRA_POINTS, {17,18,19,26}},
			{TETRA_POINTS, {0,1,9,26}},
			{PYRAMID_POINTS, {0,1,13,12,26}},
			{PYRAMID_POINTS, {12,13,5,4,26}},
			{PYRAMID_POINTS, {4,5,17,19,26}},
			{PYRAMID_POINTS, {5,17,22,13,26}},
			{PYRAMID_POINTS, {1,9,22,13,26}},
			{PRISM_POINTS, {6,17,18,14,22,23}},
			{PRISM_POINTS, {14,22,23,2,9,10}}
		}},
	{4613888, {
			{PYRAMID_POINTS, {0,8,10,3,22}},
			{TETRA_POINTS, {8,9,10,22}},
			{PYRAMID_POINTS, {3,7,18,10,22}},
			{TETRA_POINTS, {10,14,18,22}},
			{PYRAMID_POINTS, {2,9,22,14,10}},
			{PYRAMID_POINTS, {0,3,7,4,22}},
			{TETRA_POINTS, {4,7,18,22}},
			{TETRA_POINTS, {4,17,18,22}},
			{TETRA_POINTS, {0,8,4,22}},
			{TETRA_POINTS, {4,8,13,22}},
			{PYRAMID_POINTS, {5,13,22,17,4}},
			{PYRAMID_POINTS, {1,9,22,13,8}},
			{PYRAMID_POINTS, {6,14,22,17,18}}
		}},
	{411136, {
			{PRISM_POINTS, {4,7,18,0,3,10}},
			{PRISM_POINTS, {4,18,17,0,10,9}},
			{PRISM_POINTS, {4,5,17,0,1,9}},
			{PYRAMID_POINTS, {9,10,18,17,14}},
			{TETRA_POINTS, {6,14,17,18}},
			{TETRA_POINTS, {2,9,14,10}}
		}},
	{34570496, {
			{PYRAMID_POINTS, {7,18,25,19,15}},
			{TETRA_POINTS, {0,3,8,15}},
			{PYRAMID_POINTS, {0,8,25,19,15}},
			{TETRA_POINTS, {2,3,8,15}},
			{TETRA_POINTS, {2,15,25,8}},
			{TETRA_POINTS, {2,15,18,25}},
			{PYRAMID_POINTS, {6,17,25,18,2}},
			{PYRAMID_POINTS, {1,8,25,17,2}},
			{PRISM_POINTS, {1,5,17,8,16,25}},
			{PRISM_POINTS, {8,16,25,0,4,19}}
		}},
	{34554112, {
			{PYRAMID_POINTS, {6,18,25,17,14}},
			{TETRA_POINTS, {1,2,8,14}},
			{PYRAMID_POINTS, {1,8,25,17,14}},
			{TETRA_POINTS, {3,2,8,14}},
			{TETRA_POINTS, {3,14,25,8}},
			{TETRA_POINTS, {3,14,18,25}},
			{PYRAMID_POINTS, {7,19,25,18,3}},
			{PYRAMID_POINTS, {0,8,25,19,3}},
			{PRISM_POINTS, {0,4,19,8,16,25}},
			{PRISM_POINTS, {8,16,25,1,5,17}}
		}},
	{26213376, {
			{PRISM_POINTS, {0,1,11,12,13,24}},
			{PRISM_POINTS, {1,10,11,13,23,24}},
			{PRISM_POINTS, {1,2,10,13,14,23}},
			{PRISM_POINTS, {3,10,11,15,23,24}},
			{PRISM_POINTS, {15,23,24,7,18,19}},
			{PYRAMID_POINTS, {4,12,24,19,16}},
			{PYRAMID_POINTS, {6,14,23,18,17}},
			{PRISM_POINTS, {16,19,24,17,18,23}},
			{PYRAMID_POINTS, {16,17,23,24,13}},
			{TETRA_POINTS, {12,13,16,24}},
			{TETRA_POINTS, {13,14,17,23}},
			{TETRA_POINTS, {5,13,17,16}}
		}},
	{1875712, {
			{PYRAMID_POINTS, {3,10,20,11,15}},
			{TETRA_POINTS, {7,18,19,15}},
			{PYRAMID_POINTS, {0,8,20,11,12}},
			{PYRAMID_POINTS, {11,12,19,15,20}},
			{TETRA_POINTS, {12,5,19,20}},
			{TETRA_POINTS, {4,12,19,5}},
			{TETRA_POINTS, {5,8,12,20}},
			{TETRA_POINTS, {10,15,18,20}},
			{TETRA_POINTS, {18,19,20,15}},
			{TETRA_POINTS, {5,18,19,20}},
			{PRISM_POINTS, {2,6,9,10,18,20}},
			{PYRAMID_POINTS, {6,9,20,18,5}},
			{PYRAMID_POINTS, {1,8,20,9,5}}
		}},
	{156672, {
			{PYRAMID_POINTS, {0,3,7,4,10}},
			{TETRA_POINTS, {0,1,10,13}},
			{TETRA_POINTS, {0,4,13,10}},
			{PYRAMID_POINTS, {4,7,14,13,10}},
			{PYRAMID_POINTS, {1,2,14,13,10}},
			{PYRAMID_POINTS, {4,7,14,13,17}},
			{TETRA_POINTS, {5,13,17,4}},
			{TETRA_POINTS, {6,14,17,7}}
		}},
	{303104, {
			{PYRAMID_POINTS, {0,1,2,3,13}},
			{TETRA_POINTS, {4,7,15,18}},
			{TETRA_POINTS, {0,3,15,13}},
			{TETRA_POINTS, {0,4,15,13}},
			{TETRA_POINTS, {2,3,15,13}},
			{TETRA_POINTS, {4,5,13,15}},
			{TETRA_POINTS, {4,5,18,15}},
			{TETRA_POINTS, {5,13,15,18}},
			{TETRA_POINTS, {2,15,18,13}},
			{TETRA_POINTS, {2,6,18,13}},
			{TETRA_POINTS, {5,6,13,18}}
		}},
	{606208, {
			{TETRA_POINTS, {4,16,19,0}},
			{PYRAMID_POINTS, {0,1,2,3,14}},
			{TETRA_POINTS, {3,7,14,19}},
			{TETRA_POINTS, {6,7,19,14}},
			{TETRA_POINTS, {0,3,19,14}},
			{TETRA_POINTS, {0,16,19,14}},
			{TETRA_POINTS, {0,1,16,14}},
			{TETRA_POINTS, {1,5,14,16}},
			{TETRA_POINTS, {16,19,6,14}},
			{TETRA_POINTS, {5,6,16,14}}
		}},
	{856320, {
			{TETRA_POINTS, {4,16,19,12}},
			{TETRA_POINTS, {3,7,18,19}},
			{TETRA_POINTS, {0,8,12,3}},
			{TETRA_POINTS, {3,12,19,26}},
			{TETRA_POINTS, {3,18,19,26}},
			{TETRA_POINTS, {12,16,19,26}},
			{TETRA_POINTS, {16,18,19,26}},
			{TETRA_POINTS, {2,3,18,26}},
			{TETRA_POINTS, {2,6,18,26}},
			{TETRA_POINTS, {8,3,26,12}},
			{TETRA_POINTS, {2,3,8,26}},
			{TETRA_POINTS, {8,12,16,26}},
			{TETRA_POINTS, {1,2,8,26}},
			{PYRAMID_POINTS, {1,5,16,8,26}},
			{PYRAMID_POINTS, {5,6,18,16,26}},
			{PYRAMID_POINTS, {1,2,6,5,26}}
		}},
	{562176, {
			{PYRAMID_POINTS, {1,2,6,5,10}},
			{TETRA_POINTS, {1,0,10,12}},
			{TETRA_POINTS, {1,5,12,10}},
			{PYRAMID_POINTS, {5,6,15,12,10}},
			{PYRAMID_POINTS, {0,3,15,12,10}},
			{PYRAMID_POINTS, {5,6,15,12,19}},
			{TETRA_POINTS, {4,12,19,5}},
			{TETRA_POINTS, {7,15,19,6}}
		}},
	{282624, {
			{PYRAMID_POINTS, {1,0,3,2,12}},
			{TETRA_POINTS, {5,6,14,18}},
			{TETRA_POINTS, {1,2,14,12}},
			{TETRA_POINTS, {1,5,14,12}},
			{TETRA_POINTS, {3,2,14,12}},
			{TETRA_POINTS, {5,4,12,14}},
			{TETRA_POINTS, {5,4,18,14}},
			{TETRA_POINTS, {4,12,14,18}},
			{TETRA_POINTS, {3,14,18,12}},
			{TETRA_POINTS, {3,7,18,12}},
			{TETRA_POINTS, {4,7,12,18}}
		}},
	{1470208, {
			{PYRAMID_POINTS, {2,10,20,9,14}},
			{TETRA_POINTS, {6,18,17,14}},
			{PYRAMID_POINTS, {1,8,20,9,13}},
			{PYRAMID_POINTS, {9,13,17,14,20}},
			{TETRA_POINTS, {13,4,17,20}},
			{TETRA_POINTS, {5,13,17,4}},
			{TETRA_POINTS, {4,8,13,20}},
			{TETRA_POINTS, {10,14,18,20}},
			{TETRA_POINTS, {18,17,20,14}},
			{TETRA_POINTS, {4,18,17,20}},
			{PRISM_POINTS, {3,7,11,10,18,20}},
			{PYRAMID_POINTS, {7,11,20,18,4}},
			{PYRAMID_POINTS, {0,8,20,11,4}}
		}},
	{967680, {
			{TETRA_POINTS, {0,3,10,15}},
			{TETRA_POINTS, {1,2,10,14}},
			{TETRA_POINTS, {7,15,18,19}},
			{TETRA_POINTS, {0,15,18,19}},
			{PYRAMID_POINTS, {10,14,18,15,0}},
			{TETRA_POINTS, {0,1,10,14}},
			{TETRA_POINTS, {0,1,14,18}},
			{PYRAMID_POINTS, {0,1,17,19,18}},
			{TETRA_POINTS, {1,14,17,18}},
			{TETRA_POINTS, {6,17,18,14}},
			{PRISM_POINTS, {0,4,19,1,5,17}}
		}},
	{37699328, {
			{HEXA_POINTS, {20,9,2,10,25,17,6,18}},
			{HEXA_POINTS, {11,20,10,3,19,25,18,7}},
			{PRISM_POINTS, {0,12,11,8,21,20}},
			{PRISM_POINTS, {8,21,20,1,13,9}},
			{PRISM_POINTS, {12,4,19,21,16,25}},
			{PRISM_POINTS, {21,16,25,13,5,17}},
			{PRISM_POINTS, {11,12,19,20,21,25}},
			{PRISM_POINTS, {20,21,25,9,13,17}}
		}}
};


bool PatternFactory::createPattern(Uint mask) {

    const Element *el = elements;
    Uint SIZE = sizeof(elements)/sizeof(Element);

    pattern.clear();

    for (Uint i=0; i<SIZE; i++) {
        if (el[i].mask == mask) {

            const item *it = el[i].items;
            for(Uint j=0; j<MAX_ELEMENTS; j++) { 
                if (it->size == 0)
                    break;
                pattern.push_back(vector<Uint>(it->points, it->points + it->size));
                it++;
            }

            return true;
        }
    }

    return false;
}

void PatternFactory::deleteInstance () {

    if (m_Instance) {
        delete m_Instance;
        m_Instance = NULL;
    }

}

PatternFactory* PatternFactory::instance() {

    if (!m_Instance) {
        m_Instance = new PatternFactory();
    }
    else
        cout << "INSTANCE ALREADY CREATED" << endl;

    //m_NumInstances++;
    return m_Instance;
}

}

