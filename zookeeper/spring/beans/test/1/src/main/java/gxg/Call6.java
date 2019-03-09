package gxg;

import org.springframework.beans.factory.BeanFactory;
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
public class Call6 {
    public static void main(String[] args) {
        ConfigurableApplicationContext ctx = SpringApplication.run(Call6.class, args);
        BeanFactory bf = ctx.getBeanFactory();
        System.out.println(bf.getBean("Comp"));
        System.out.println(bf.getBean("testBean"));
        ctx.close();
    }
}