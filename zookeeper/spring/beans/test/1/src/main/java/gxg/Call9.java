package gxg;

import gxg.beans.Comp;
import gxg.beans.TestBean;
import org.springframework.beans.factory.BeanFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.ApplicationRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

@SpringBootApplication
public class Call9 {
    @Autowired private BeanFactory bf;
    @Autowired private Comp comp;
    @Autowired private TestBean testBean;

    @Bean
    public ApplicationRunner runner() {
        return args -> {
//            System.out.println(bf.getBean("Comp"));
//            System.out.println(bf.getBean("testBean"));
//            System.out.println(comp);
//            System.out.println(testBean);
        };
    }

    public static void main(String[] args) {
        SpringApplication.run(Call9.class, args).close();
    }
}
