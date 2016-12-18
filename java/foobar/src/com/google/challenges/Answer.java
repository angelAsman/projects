package com.google.challenges; 

import java.util.ArrayList;
import java.util.HashMap;

/* Answer.java
 * Version 1
 * Scores names in a list by the Lexicographic score and sorts the highest score to the top of the list reguardless
 * of length
 */
public class Answer {
		
    public static String[] answer(String[] names) { 
    	
    	class Names{
    		String name;
    		int  score;
    	}
    	
    	char[] alphabet = "abcdefghijklmnopqrstuvwxyz".toCharArray();
    	HashMap<String, Integer> alphaMap = new HashMap<String, Integer>();
    	
    	int i = 0;
    	for (char a: alphabet){
    		String s = Character.toString(a);
    		i++;
    		alphaMap.put(s, i);
    		
    	}
    	
  /* populate the list by the score
   *   	
   */
    	HashMap<String, Integer> Namescore = new HashMap<String, Integer>();
    	ArrayList<Names> nameList = new ArrayList<Names>();
    	
    	for (String name: names){
    		Names nameObject = new Names();
    		int score = 0;
    		for(i=0; i< name.length(); i++){

    			char c = name.charAt(i);
    			String letter = Character.toString(c);
    			score += alphaMap.get(letter);
    			
    		}

    		nameObject.name = name;
    		nameObject.score = score;
    		nameList.add(nameObject);   		
    		Namescore.put(name, score);
    		
    	}
    	
 /* Sort the list by insertion sort
  *   	
  */
    	Names[] sortedNames = new Names[nameList.size()];
    	sortedNames = nameList.toArray(sortedNames);
    	
    	for(i=1; i<sortedNames.length; i++){
    		Names n = sortedNames[i];
    		int temp = sortedNames[i].score;
    		int j;
  		
    		for(j=i-1; j>=0 && temp > sortedNames[j].score; j--){
    			
    			sortedNames[j+1] = sortedNames[j];   			
    		}
    		
    		sortedNames[j+1] = n;
    	}
    		

        	
    	for(i=1; i<sortedNames.length; i++){
    		Names n = sortedNames[i];
    		int temp = sortedNames[i].score;
    		String name = sortedNames[i].name;
    		int j;
    		
    		for(j=i-1; j>=0 && name.compareTo(sortedNames[j].name) > 0 && temp == sortedNames[j].score; j--){
 			
    			sortedNames[j+1] = sortedNames[j];   			
    		}
    		
    		sortedNames[j+1] = n;
    	}
    	
 /*
  * Add names to list 	
  */
    	String[] finalNames = new String[sortedNames.length];
    	
		for(i=0; i< sortedNames.length; i++){
			finalNames[i] = sortedNames[i].name;

			System.out.println(finalNames[i]);

		}
    	   	    
    	return finalNames;
    	
    
    } 
        
    public static void main(String [ ] args){
    	//String[] names = {"bonnie", "liz", "annie", "cj", "al"};
    	String[] names = {"amaa","cjc","oa","aaaaaaaaaaaaaaaa","cjba"};
    	answer(names);
    	
    }
}
