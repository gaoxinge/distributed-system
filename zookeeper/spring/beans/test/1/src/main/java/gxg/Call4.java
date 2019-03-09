package gxg;

import org.springframework.beans.factory.config.ConfigurableListableBeanFactory;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class Call4 {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext ctx = new AnnotationConfigApplicationContext("gxg.beans");
//        ctx.start();
        ConfigurableListableBeanFactory bf = ctx.getBeanFactory();
        System.out.println(bf.getBean("Comp"));
        System.out.println(bf.getBean("testBean"));
    }
}
