package gxg;

import gxg.beans.Comp;
import gxg.beans.TestBean;
import org.springframework.beans.factory.BeanFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;

//@EnableAutoConfiguration
//@ComponentScan("gxg.beans")
//@EnableAutoConfiguration
//@ComponentScan
@SpringBootApplication
public class Call7 implements CommandLineRunner {
    @Autowired private BeanFactory bf;
    @Autowired private Comp comp;
    @Autowired private TestBean testBean;

    @Override
    public void run(String... args) {
//        System.out.println(bf.getBean("Comp"));
//        System.out.println(bf.getBean("testBean"));
//        System.out.println(comp);
//        System.out.println(testBean);
    }

    public static void main(String[] args) {
        SpringApplication.run(Call7.class, args).close();
    }
}