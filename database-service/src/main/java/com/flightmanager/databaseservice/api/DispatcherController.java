package com.flightmanager.databaseservice.api;

import com.flightmanager.databaseservice.models.DispatcherModel;
import com.flightmanager.databaseservice.repos.DispatcherRepo;
import jdk.internal.loader.Loader;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.RequestEntity;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.logging.Logger;

@RestController
public class DispatcherController {

    @Autowired
    private DispatcherRepo repo;

    @GetMapping("${mapping.dispatcher.get}/{id}")
    public ResponseEntity<DispatcherModel> get(@PathVariable("id") long id) {
        try{
            DispatcherModel model = repo.findById(id).orElse(null);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }
    @PostMapping("${mapping.dispatcher.create}")
    public ResponseEntity<DispatcherModel> get(@RequestBody() DispatcherModel data) {
        try{
            data.setId(0L);
            DispatcherModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.dispatcher.update}")
    public ResponseEntity<DispatcherModel> update(@RequestBody() DispatcherModel data) {
        try{
            if(repo.findById(data.getId()).orElse(null) == null)
                return ResponseEntity.status(400).build();
            DispatcherModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.dispatcher.delete}/{id}")
    public ResponseEntity<Void> delete(@PathVariable("id") long id) {
        try{
            repo.deleteById(id);
            return ResponseEntity.ok().build();
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

}
