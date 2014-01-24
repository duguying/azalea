/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include "net/message.h"

/**
 * 调制
 * @param  string [description]
 * @return        [description]
 */
Frame* msg_modulate(char* string){
	/// string total length
	int total_length;
	/// total frame numbers
	int frame_number;
	/// 进位
	int carry=1;
	/// frames
	Frame* frames;
	int i=0;

	total_length=strlen(string);
	if(0==total_length%FRAME_LEN){
		carry=0;
	}

	frame_number=(int)(total_length/FRAME_LEN)+carry;
	frames=(Frame*)malloc(sizeof(Frame)*frame_number);
	memset(frames,0,sizeof(Frame)*frame_number);

	for(i=0;i<frame_number;i++){
		frames[i].cf=i+1;
		frames[i].tf=frame_number;
		strncpy(frames[i].content,string+i*FRAME_LEN,FRAME_LEN);
		// printf("\033[1;34mtotal_length:%d, frame_number:%d, current_frame:%d\033[1;0m\n%s\n\n", total_length, frame_number, i+1, frames[i].content);
	}

	return frames;
}

/**
 * 解调
 * @param  frame [description]
 * @return       [description]
 */
char* msg_demodulate(Frame* frames){
	int frame_number=0;
	char* string;
	int i=0;

	frame_number=frames[0].tf;

	if(frame_number<=0){
		return (void*)-1;//error
	}

	string=(char*)malloc(sizeof(char)*(frame_number*FRAME_LEN));
	memset(string,0,sizeof(char)*(frame_number*FRAME_LEN));

	for(i=0;i<frame_number;i++){
		strncpy(string+i*FRAME_LEN,frames[i].content,FRAME_LEN);
	}

	return string;
}

/**
 * push message into message buffer
 * @param  frame_pointer frame buffer
 * @param  frame         single message frame
 * @return               message string
 */
char* msg_frame_buffer_push(Frame* frame_pointer, Frame* frame){
	char* message;

	if (1==frame->cf)
	{
		frame_pointer=(Frame*)malloc(sizeof(Frame)*frame->tf);
	}
	if (NULL==frame_pointer)
	{
		printf("error, `frame_pointer` is empty!");
		return (void*)-1;
	}
	strncpy((char*)frame_pointer,(char*)frame,sizeof(Frame));
	if (frame->tf==frame->cf)
	{
		message = msg_demodulate(frame_pointer);
		free(frame_pointer);
		return message;
	}
	return NULL;
}
