package gxg;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ConfigurableApplicationContext;
import org.springframework.context.annotation.ComponentScan;

//@EnableAutoConfiguration
//@ComponentScan("gxg.beans")
//@EnableAutoConfiguration
//@ComponentScan
@SpringBootApplication
public class Call5 {
    public static void main(String[] args) {
        ConfigurableApplicationContext ctx = SpringApplication.run(Call5.class, args);
        System.out.println(ctx.getBean("Comp"));
        System.out.println(ctx.getBean("testBean"));
        ctx.close();
    }
}