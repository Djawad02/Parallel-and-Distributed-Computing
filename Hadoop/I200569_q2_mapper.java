package dblp;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class I200569_q2_mapper extends Mapper <LongWritable, Text, Text, IntWritable> {

    
    private Text CoAuthorsCount = new Text();
    public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {

    	//getting data from csv file line by line in string
        String line = value.toString();
        String[] fields = line.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1); //setting its pattern for correct access
        
        String authorsString = fields[1].trim();	//getting respective values from csv
        String journalName = fields[5].trim();
        
        //cleaning the authors list from quotation marks and brackets
        authorsString = authorsString.substring(1, authorsString.length() - 1);
        authorsString = authorsString.replace("[", "").replace("]", "");
        
        String[] authorsList = authorsString.split("',\\s*'");
        List<String> authorsArr = Arrays.asList(authorsList);

        for (int i = 0; i < authorsArr.size()- 1; i++) {
            for (int j = i + 1; j < authorsArr.size(); j++) {
                String author1 = authorsArr.get(i).replaceAll("'", ""); 
                String author2 = authorsArr.get(j).replaceAll("'", ""); 
                
                if (!author1.equals(author2)) {  //check for two different authors not duplicates
                    List<String> coAuthorsList = new ArrayList<>();
                    coAuthorsList.add(author1);
                    coAuthorsList.add(author2);
                    Collections.sort(coAuthorsList);  // so that auth1,auth2 and auth2,auth1 dont lead to two different keys
                    String coAuthorsString = String.join(" & ", coAuthorsList);
                    
                    //setting key
                    CoAuthorsCount.set("Authors:  "+coAuthorsString + "  ,  "+" journal: "+ journalName +  ",  count=");
                    context.write(CoAuthorsCount, new IntWritable(1));
                }
            }
        }
    }
}
