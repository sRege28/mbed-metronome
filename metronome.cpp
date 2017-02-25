#include "metronome.hpp"
/*
* This file provides the functonality of the metronome - logging beats 
* and calculating the difference between them(deltas). The board takes a running
* average of these deltas and stores them as bpm value. 
*/

//Resets the board to log new beats

void metronome::reset()
{
    m_beat_count =0;
    m_prev_beat =0;
    m_curr_beat=0;
    bpm = 0.0;
}

//Starts the Timer object to get the time on button press

void metronome::start_timing()
{ 
  reset();
  m_timing = true;
  log_on_terminal("Entered learn mode... Please press the SW2 button to log beats\n");   
  m_timer.start(); 
}

//Stops the Timer object and cleans up

void metronome::stop_timing()
{
 m_timing = false;
 log_on_terminal("Entered play mode... Playing the beats\n"); 
 m_timer.stop();
 //printf("The BPM calculated so far is %f\n",get_bpm());
   
}


//Listens for button press event 

void metronome::tap()
{
   if(m_timing){
    float time = m_timer.read();
    printf("%f \r\n", time);
    m_beat_count++;
    printf(" count %i \n",m_beat_count);
    calc_deltas(time, m_beat_count);
   }
   else{printf("Not in learn mode");}
}

//Calculates the difference between the beats and running average

void metronome::calc_deltas(float t, int count)
{
   
  if(m_prev_beat==0)
  {
      m_prev_beat = t;
      //m_beat_count=1;
  }
  else
  {
      m_curr_beat = t;      
      float delta = m_curr_beat - m_prev_beat;
      m_prev_beat = m_curr_beat;
      printf("Delta is %f \r\n", delta);
      printf("Count is %i\n", count);
      if(count<=1)
      {
          printf("Not enough values yet!bpm is %f\n",bpm);
      }
      if(count==2)
      {   
          bool x = (delta==bpm);
          printf("Is delta = bpm? %d\n",x);
          bpm = delta;
          printf("First bpm is %f\n",bpm);
      }
      else
      {   printf("Old average %f ",bpm);
          printf("%f / %f + %f =",bpm,(float)(count-2),delta);
          float sum = bpm*(float)(count-2) + delta;
          printf("%f\n New Average = %f / %f",sum,sum,(float)(count-1));
          bpm = sum/(float)(count-1);
          printf("BPM is %f\n",bpm);
      }   
  }
}

// Returns the average time between beats

float metronome::get_beat()
{  
  if(m_beat_count < 4)
    return 0;
  else  
    return bpm;
}

// Returns the average BPM - Beats Per Minute

float metronome::get_bpm()
{
    if(m_beat_count<4)
     return 0;
    else return (float)(60/bpm);
}