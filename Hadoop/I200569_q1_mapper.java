package dblp;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.io.LongWritable;

public class I200569_q1_mapper extends Mapper <LongWritable, Text, Text, IntWritable>{

	private Text JournallCount = new Text();

    public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {

    	//getting data from csv file line by line in string
    	String L1 = value.toString();
        String pat = ",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)"; //setting its pattern for correct access
        String[] fields = L1.split(pat, -1);
        
        String year = fields[2];	//getting respective values from csv
		String journalName = fields[5].trim();
		
		//setting key
		JournallCount.set("journal:  "+journalName + "  ,  " +" year: "+ year + ",  count="); 	//setting key
        context.write(JournallCount, new IntWritable(1));
     }
}
    