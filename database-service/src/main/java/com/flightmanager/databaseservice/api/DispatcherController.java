package com.flightmanager.databaseservice.api;

import com.flightmanager.databaseservice.models.AirportModel;
import com.flightmanager.databaseservice.models.DispatcherModel;
import com.flightmanager.databaseservice.models.PlaneModel;
import com.flightmanager.databaseservice.models.RoleModel;
import com.flightmanager.databaseservice.repos.DispatcherRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import javax.persistence.ElementCollection;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Set;

@RestController
public class DispatcherController {

    @Autowired
    private DispatcherRepo repo;


    @GetMapping("${mapping.dispatcher.get}")
    public ResponseEntity<ArrayList<DispatcherModel>> getAll() {
        try{
            ArrayList<DispatcherModel> models = (ArrayList<DispatcherModel>) repo.findAll();
            return ResponseEntity.ok(models);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

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
    @GetMapping("${mapping.dispatcher.get}/{email}")
    public ResponseEntity<DispatcherModel> get(@PathVariable("email") String email) {
        try{
            DispatcherModel model = repo.findByEmail(email).orElse(null);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }
    @PostMapping("${mapping.dispatcher.create}")
    public ResponseEntity<DispatcherModel> get(@RequestBody DispatcherModel data) {
        try{
            data.setId(0L);
            if(containsNullFields(data))
                return ResponseEntity.status(400).build();
            DispatcherModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.dispatcher.update}")
    public ResponseEntity<DispatcherModel> update(@RequestBody DispatcherModel data, @RequestParam("update") String update) {
        try{
            if(data.getId() == null)
                return ResponseEntity.status(400).build();
            DispatcherModel fromDB = repo.findById(data.getId()).orElse(null);
            if(fromDB == null)
                return ResponseEntity.status(400).build();

            ArrayList<String> fields = new ArrayList<>(Arrays.asList(update.split(",")));
            if(!fields.contains("firstName"))
                data.setFirstName(fromDB.getFirstName());
            if(!fields.contains("lastName"))
                data.setLastName(fromDB.getLastName());
            if(!fields.contains("email"))
                data.setEmail(fromDB.getEmail());
            if(!fields.contains("password"))
                data.setPassword(fromDB.getPassword());
            if(!fields.contains("isBanned"))
                data.setIsBanned(fromDB.getIsBanned());
            if(!fields.contains("roles"))
                data.setRoles(fromDB.getRoles());
            if(containsNullFields(data))
                return ResponseEntity.status(400).build();

            DispatcherModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @DeleteMapping("${mapping.dispatcher.delete}/{id}")
    public ResponseEntity<Void> delete(@PathVariable("id") long id) {
        try{
            repo.deleteById(id);
            return ResponseEntity.ok().build();
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    private boolean containsNullFields(DispatcherModel data){
         return data.getFirstName() == null ||
                data.getLastName() == null ||
                data.getEmail() == null ||
                data.getPassword() == null ||
                data.getIsBanned() == null ||
                data.getRoles() == null;
    }

}
