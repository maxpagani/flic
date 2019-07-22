/**
 * @file lambda.hh
 * @author Massimiliano Pagani (maxpag@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-07-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#if !defined( FLIC_LAMBDA_HH )
#define  FLIC_LAMBDA_HH 

#define Lambda(x,f)  []( auto& x ){ return (f); }

#endif