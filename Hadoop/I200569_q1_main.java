package dblp;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

public class I200569_q1_main {
	public static void main(String[] args) throws Exception{
		
	Configuration conf = new Configuration();
	String[] pathArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
	if (pathArgs.length < 2){
	System.err.println("MR Project Usage: Journals' Count Per Year <input-path> […] <output-path>");
	System.exit(2);
	}
	Job wcJob = Job.getInstance(conf, "MapReduce Journals' Count Per Year ");
	wcJob.setJarByClass(I200569_q1_main.class);
	wcJob.setMapperClass(I200569_q1_mapper.class);
	wcJob.setCombinerClass(I200569_q1_reducer.class);
	wcJob.setReducerClass(I200569_q1_reducer.class);
	wcJob.setOutputKeyClass(Text.class);
	wcJob.setOutputValueClass(IntWritable.class);
	for (int i = 0; i < pathArgs.length - 1; ++i){
		FileInputFormat.addInputPath(wcJob, new Path(pathArgs[i]));
	}
	FileOutputFormat.setOutputPath(wcJob, new Path(pathArgs[pathArgs.length - 1]));
	System.exit(wcJob.waitForCompletion(true) ? 0 : 1);
	}
}
